#include "Fish.h"

//Constructors and destructors
Fish::Fish(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, float hp, float speed): 
GameObject(position, size, angle, texture), hp(hp), speed(speed), isCought(false)
{
}

Fish::~Fish(void)
{
}

//Functions
void Fish::update(void)
{
	if(isCought==false)
		position.set_X(position.get_X()-speed);
}

