#include "Barrel.h"

//Constructors and destructors

Barrel::Barrel(const FloatingObject & floatingObject, const float health, const float speed, const float damage, const unsigned int scor):
	FloatingObject(floatingObject), 
	health(fabs(health)),
	speed(fabs(speed)),
	damage(fabs(damage)),
	scor(scor)
{
}


Barrel::~Barrel(void)
{
	FloatingObject::~FloatingObject();
}

//Functions
void Barrel::free()
{
	bonusList.clear();
}

void Barrel::update()
{		
	FloatingObject::setPositionX(position.get_X()-speed);
	FloatingObject::update();	
}

void Barrel::onCollision(const float power)
{
	health-=power;

	if(health<=0)
	{
		onCollision();
		createBonus();
	}
}

void Barrel::createBonus()
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

std::ostream & operator<< (std::ostream & w, const Barrel &b)
{
	return w<<b.health<<" "<<b.speed<<" "<<b.damage<<" "<<b.scor<<" "<<b.front<<" "<<b.back<<" "
	<<b.difference<<" "<<b.textureName<<" "<<b.position<<" "<<b.size<<" "<<b.angle<<" "<<b._isDestroyed<<std::endl; 
}
std::istream & operator>> (std::istream &w, Barrel & b)
{	
	w>>b.health>>b.speed>>b.damage>>b.scor>>b.front>>b.back>>b.difference>>b.textureName>>b.position>>b.size>>b.angle>>b._isDestroyed;
	return w;
}
Barrel::SampleBonusList Barrel::initializeBonusList()
{
	SampleBonusList list;
	SampleBonus bonus;
	std::ifstream file(resourcesPath+bonusFile);

	if(file.is_open())//error
	{
		while(!file.eof())
		{
			file>>bonus;
			list.push_back(bonus);
		}
	}	
	return list;
}

Barrel::SampleBonusList Barrel::bonusList = Barrel::initializeBonusList();