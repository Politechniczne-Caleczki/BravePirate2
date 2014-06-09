#include "Cannon.h"

//Constructors and destructors

Cannon::Cannon(const float angle, const float power, const Vector2 position):angle(0), power(0), position(position), interval(200)
{
}

Cannon::~Cannon(void)
{
	this->cannonBalls.clear();
}

//Getters and setters
void Cannon::setAngle(const float angle)
{
	this->angle = angle;
}

void Cannon::setPosition(const Vector2 position)
{
	this->position = position;
}

void Cannon::setInterval(const Delay interval)
{
	this->interval = interval;
}

//Functions
void Cannon::fire(void)
{
	if(interval.idRedy())
	{
		interval.Start();	
		cannonBalls.push_back(CannonBall(position, Vector2(10,10), angle, Textures::getTexture("cannonball.png"), 0.4f, 10, 10 ));
	}
}

void Cannon::update(void)
{
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE])
	{
		fire();		
	}
	
	for(list<CannonBall>::iterator iter = cannonBalls.begin(); iter != cannonBalls.end(); )
	{
		iter->update();
		if(iter->isDestroyed())
		{			
			iter = cannonBalls.erase(iter);
		}
		else
			iter++;
	}
	interval.update();
}

void Cannon::draw(void)const
{	
	for(list<CannonBall>::const_iterator iter = cannonBalls.begin(); iter != cannonBalls.end(); iter++)
	{
		iter->draw();
	}
}