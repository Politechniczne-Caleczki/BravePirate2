#pragma once
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"
#include "Fish.h"

class FishingRod: public GameObject
{
private:
	GameObject *catchObject;
	float descentRate,  descent,  maxDepth;
	Vector2 positionOfShip;
	void checkCollisions(void);
public:
	FishingRod(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const float descentRate, const float maxDepth);
	
	GameObject *getCatchObject(void);
	float getDescentRate(void)const;
	float getMasDepth(void)const;
	void setDescentRate(const float rate);
	void setMaxDepth(const float depth);
	void setPosition(const Vector2 newPosition);
	
	void update(void);
	void draw(void)const;

};

inline float FishingRod::getDescentRate(void)const
{
	return this->descentRate;
}

inline float FishingRod::getMasDepth(void)const
{
	return this->maxDepth;
}
inline void FishingRod::setDescentRate(const float rate)
{
	this->descentRate = rate;
}

inline void FishingRod::setMaxDepth(const float depth)
{
	this->maxDepth = depth;
}