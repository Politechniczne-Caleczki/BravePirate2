#include "Metal.h"

//Constructors and destructors
Metal::Metal(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float value): 
BonusObject(position, size, angle, textureName, energyBonus, value, 0)
{
}

Metal::~Metal(void)
{
}

//Functions
void Metal::update(void)
{	
	position.set_X(position.get_X() + Desert::getDelta());
}

std::ostream & operator<< (std::ostream &w, const Metal &f)
{
	return w<<1<<" "<<f.angle<<" "<<f.position<<" "<<f.size
		<<" "<<f.textureName<<" "<<(int)f.type<<" "<<f.value<<std::endl;
}

std::istream & operator>> (std::istream &w, Metal &f)
{
	int typ=0;
	w>>f.angle>>f.position>>f.size
		>>f.textureName>>typ>>f.value;
	f.setType((Metal_Bonus_Types)typ);
	f.texture = Textures::getTexture(f.textureName);
	return w;
}
