#include "Fish.h"

//Constructors and destructors
Fish::Fish(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float value, float speed): 
BonusObject(position, size, angle, textureName, energyFish, value, speed)
{
}

Fish::~Fish(void)
{
}

//Functions
void Fish::update(void)
{	
	position.set_X(position.get_X()- speed*Time::deltaTime());
}

std::ostream & operator<< (std::ostream &w, const Fish &f)
{
	return w<<" "<<f.angle<<" "<<f.position<<" "<<f.size<<" "<<f.speed
		<<" "<<f.textureName<<" "<<(int)f.type<<" "<<f.value<<std::endl;
}

std::istream & operator>> (std::istream &w, Fish &f)
{
	int typ=0;
	w>>f.angle>>f.position>>f.size>>f.speed
		>>f.textureName>>typ>>f.value;
	f.setType((Fishs_Gifts_Types)typ);
	f.texture = Textures::getTexture(f.textureName);
	return w;
}
