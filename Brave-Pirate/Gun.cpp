#include "Gun.h"

//Constructors and destructors

Gun::Gun(const float angle, const float power, const Vector2 position, const Delay interval , const float requiredEnergy)
	:angle(angle), power(power), position(position), interval(interval),requiredEnergy(fabs(requiredEnergy))
{
}

Gun::~Gun(void)
{
	this->ammos.clear();
}


//Functions
void Gun::fire(void)
{
	if(interval.idRedy()&& Player::getInstance().getPlayerEnergy()>requiredEnergy)
	{
		interval.Start();	
		ammos.push_back(Ammo(position, ammoSize , angle, ammoTextures, ammoSpeed, power ));
		Player::getInstance().removePlayerEnery(requiredEnergy);
	}
}

void Gun::update(void)
{
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE])
	{
		fire();		
	}
	
	for(std::list<Ammo>::iterator iter = ammos.begin(); iter != ammos.end(); )
	{
		iter->update();
		if(iter->isDestroyed())
		{			
			iter = ammos.erase(iter);
		}
		else
			iter++;
	}
	interval.update();
}

void Gun::draw(void)const
{	
	for(std::list<Ammo>::const_iterator iter = ammos.begin(); iter != ammos.end(); iter++)
	{
		iter->draw();
	}
}

std::ostream & operator<< (std::ostream &w, const Gun &c)
{
	w<<c.angle<<" "<<c.power<<" "<<c.requiredEnergy<<" "
		<<c.position<<" "<<c.interval<<std::endl<<c.ammos.size()<<std::endl;

	for(list<Ammo>::const_iterator iter = c.ammos.begin(); iter != c.ammos.end(); iter++)
		w<<*iter<<" ";
	return w;
}


std::istream & operator>> (std::istream &w, Gun &c)
{
	Ammo ball(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 0.4f, 10 );
	int numberOfCannonballs =0;
	w>>c.angle>>c.power>>c.requiredEnergy>>c.position>>c.interval>>numberOfCannonballs;
	c.ammos.clear();
	for(int i=0;i<numberOfCannonballs;i++)
	{
		w>>ball;
		c.ammos.push_back(ball);
	}
	return w;
}