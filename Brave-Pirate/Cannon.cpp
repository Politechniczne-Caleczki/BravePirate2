#include "Cannon.h"

//Constructors and destructors

Cannon::Cannon(const float angle, const float power, const Vector2 position, const unsigned int requiredEnergy):angle(0), power(0), position(position), interval(200),requiredEnergy(requiredEnergy)
{
}

Cannon::~Cannon(void)
{
	this->cannonBalls.clear();
}


//Functions
void Cannon::fire(void)
{
	if(interval.idRedy()&& Player::getInstance().getPlayerEnergy()>requiredEnergy)
	{
		interval.Start();	
		cannonBalls.push_back(CannonBall(position, Vector2(10,10), angle, "cannonball.png", 0.4f, 10 ));
		Player::getInstance().removePlayerEnery(requiredEnergy);
	}
}

void Cannon::update(void)
{
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE])
	{
		fire();		
	}
	
	for(std::list<CannonBall>::iterator iter = cannonBalls.begin(); iter != cannonBalls.end(); )
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
	for(std::list<CannonBall>::const_iterator iter = cannonBalls.begin(); iter != cannonBalls.end(); iter++)
	{
		iter->draw();
	}
}