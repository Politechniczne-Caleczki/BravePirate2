#pragma once
#include "GameObject.h"
#include "Fish.h"
class Fish: public GameObject
{
private:
	float hp, speed;
	bool isCought;

public:
	Fish(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, float hp, float speed);

	void update(void);
	float getHp(void);
	bool getCought(void);
	void cought(void);
};