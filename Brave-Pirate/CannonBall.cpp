#include "CannonBall.h"

//Constructors and destructors
CannonBall::CannonBall(void):speed(0),strikingDistance(0),strikingPower(0), posZero(Vector2(0,0)),startTime((float)Time::gameTime())
{
}

CannonBall::~CannonBall(void)
{	
}

CannonBall::CannonBall(const GameObject gameObject, const float speed, const float strikingDistance, const float strikingPower):
GameObject(gameObject), 
	speed(speed), 
	strikingDistance(strikingDistance), 
	strikingPower(strikingPower), 
	posZero(gameObject.getPosition()), 
	startTime((float)Time::gameTime())
{	
	tcos = (float)cos(angle*PI/180);
	tsin = (float)sin(angle*PI/180);
}

//Functions
void CannonBall::update(void)
{		
	float move = (Time::gameTime() -startTime)* speed;

	position.set_X(posZero.get_X() + (move * tcos));
	position.set_Y(posZero.get_Y() - (move * tsin) + (Time::gameTime() -startTime)*(Time::gameTime() -startTime)/6000);

	if(position.get_Y() > Sea::getWaveHeight(position.get_X()))
		_isDestroyed=true;

	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end(); iter++)
	{
		if(onCollision(*(*iter)))
		{
			_isDestroyed=true;
			(*iter)->onCollision(strikingPower*strikingDistance);
			break;
		}
	}

	GameObject::update();
}   



float CannonBall::getPower()
{
	return strikingPower*strikingDistance;
}