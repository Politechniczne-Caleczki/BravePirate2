#include "Obstacle.h"

//Constructors and destructors

Obstacle::Obstacle(const FloatingObject & floatingObject, const float health, const float speed, const float damage, const unsigned int scor):
	FloatingObject(floatingObject), 
	health(fabs(health)),
	speed(fabs(speed)),
	damage(fabs(damage)),
	scor(scor)
{
	atexit(free);
}


Obstacle::~Obstacle(void)
{
	FloatingObject::~FloatingObject();
}

//Functions
void Obstacle::free()
{
	bonusList.clear();
}

void Obstacle::update()
{		
	FloatingObject::setPositionX(position.get_X()-speed);
	FloatingObject::update();	
}

void Obstacle::onCollision(const float power)
{
	health-=power;

	if(health<=0)
	{
		onCollision();
		createBonus();
	}
}

void Obstacle::createBonus()
{

	if(bonusList.size()>0)
	{
		unsigned int r = rand()%100;

		if(r<CHANCE_FOR_A_BONUS)
		{
			r = rand()%bonusList.size();
			SampleBonusList::iterator iter = bonusList.begin();
			for(; r>0 && iter != bonusList.end() ; --r, iter++);
			if(iter != bonusList.end())
				fishesArrayPointer.push_back(new Bonus(position, (*iter).size,0, (*iter).textureName, (*iter).value, (*iter).speed,
				rand()%(int)(GraphicDevice::getInstance().getWindowSize().get_Y()-position.get_Y())+ position.get_Y(),(*iter).type));
		}
	}
}

std::ostream & operator<< (std::ostream & w, const Obstacle &b)
{
	return w<<b.health<<" "<<b.speed<<" "<<b.damage<<" "<<b.scor<<" "<<b.front<<" "<<b.back<<" "
	<<b.difference<<" "<<b.textureName<<" "<<b.position<<" "<<b.size<<" "<<b.angle<<std::endl; 
}
std::istream & operator>> (std::istream &w, Obstacle & b)
{	
	w>>b.health>>b.speed>>b.damage>>b.scor>>b.front>>b.back>>b.difference>>b.textureName>>b.position>>b.size>>b.angle;
	return w;
}

void Obstacle::loadBonus(const std::string filename)
{
	SampleBonus bonus;
	std::ifstream file(filename);

	if(file.is_open())//error
	{
		while(!file.eof())
		{
			file>>bonus;
			bonusList.push_back(bonus);
		}
	}else throw GameError("File not found: ", filename);
}

Obstacle::SampleBonusList Obstacle::initializeBonusList()
{
	SampleBonusList list;	
	return list;
}

Obstacle::SampleBonusList Obstacle::bonusList = Obstacle::initializeBonusList();