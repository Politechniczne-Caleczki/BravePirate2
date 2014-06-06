#pragma once
#include "GameObject.h"

class Fish: public GameObject
{
private:
	float hp, speed;
	bool isCought;

public:
	Fish(GameObject gameobject, float hp, float speed);
	void update(void);
	float getHp(void);
	bool cought(void);
};