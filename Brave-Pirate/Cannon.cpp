#include "Cannon.h"

//Constructors and destructors

Cannon::Cannon(const float angle, const float power, const Vector2 position, const Delay interval , const float requiredEnergy)
	:angle(angle), power(power), position(position), interval(interval),requiredEnergy(fabs(requiredEnergy))
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
		cannonBalls.push_back(CannonBall(position, cannonBallSize , angle, cannonBallTextures, cannonBallSpeed, power ));
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

std::ostream & operator<< (std::ostream &w, const Cannon &c)
{
	w<<c.angle<<" "<<c.power<<" "<<c.requiredEnergy<<" "
		<<c.position<<" "<<c.interval<<std::endl<<c.cannonBalls.size()<<std::endl;

	for(list<CannonBall>::const_iterator iter = c.cannonBalls.begin(); iter != c.cannonBalls.end(); iter++)
		w<<*iter<<" ";
	return w;
}


std::istream & operator>> (std::istream &w, Cannon &c)
{
	CannonBall ball(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 0.4f, 10 );
	int numberOfCannonballs =0;
	w>>c.angle>>c.power>>c.requiredEnergy>>c.position>>c.interval>>numberOfCannonballs;
	c.cannonBalls.clear();
	for(int i=0;i<numberOfCannonballs;i++)
	{
		w>>ball;
		c.cannonBalls.push_back(ball);
	}
	return w;
}