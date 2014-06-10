#include "Fish.h"

//Constructors and destructors
Fish::Fish(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, float hp, float speed): 
GameObject(position, size, angle, texture), hp(hp), speed(speed), isCought(false)
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
	position.set_X(position.get_X()-speed);
	SDL_Log("edfds");
}

bool Fish::cought(void)
{
	return isCought;
}


