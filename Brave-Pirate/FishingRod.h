#pragma once
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"
#include "Fish.h"
class FishingRod: public GameObject
{
private:
	float descentRate,  descent,  maxDepth;
	Vector2 positionOfShip;

public:
	FishingRod(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const float descentRate, const float maxDepth);
	
	float getDescentRate(void)const;
	float getMasDepth(void)const;
	void setDescentRate(const float rate);
	void setMaxDepth(const float depth);
	void setPosition(const Vector2 newPosition);
	
	void update(void);
	void draw(void)const;

};