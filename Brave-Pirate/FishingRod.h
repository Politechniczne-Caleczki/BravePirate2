#pragma once
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"

class FishingRod: public GameObject
{
private:
	float descentRate,  descent,  maxDepth;
	Vector2 positionOfShip;

public:
	FishingRod(const GameObject gameObject, const float descentRate, const float maxDepth, const Vector2 position);
	
	float getDescentRate(void)const;
	float getMasDepth(void)const;
	void setDescentRate(const float rate);
	void setMaxDepth(const float depth);
	void setPosition(const Vector2 newPosition);
	
	void update(void);
	void draw(void)const;
	void checkCollision(void);
};