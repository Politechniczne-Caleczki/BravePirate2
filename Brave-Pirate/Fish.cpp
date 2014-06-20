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

