#include "CannonBall.h"

//Constructors and destructors
CannonBall::~CannonBall(void)
{
}

CannonBall::CannonBall(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const float speed, const float strikingDistance, const float strikingPower):
	GameObject(position,size,angle,texture),
	speed(speed), 
	strikingDistance(strikingDistance), 
	strikingPower(strikingPower), 
	posZero(position),
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



