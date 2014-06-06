#include "Fish.h"

//Constructors and destructors
Fish::Fish(GameObject gameObject, float hp, float speed): GameObject(gameObject), hp(hp), speed(speed), isCought(false)
{
}

//Getters and setters
float Fish::getHp(void)
{
	return hp;
}

//Functions
void Fish::update(void)
{
	if(!isCought)
		position.set_X(position.get_X()+speed);
}

bool Fish::cought(void)
{
	return isCought;
}

