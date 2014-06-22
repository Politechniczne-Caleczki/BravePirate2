#ifndef FishingRod_h
#define FishingRod_h
#pragma once
#include "GameObject.h"
#include "Time.h"

class FishingRod: public GameObject
{
private:
	GameObject *catchObject;
	float descentRate,  descent;
	Vector2 positionOfShip;
	void checkCollisions(void);
public:
	FishingRod(const Vector2 position, const Vector2 size, const float angle, const std::string, const float descentRate);
	
	GameObject *getCatchObject(void);
	float getDescentRate(void)const;
	void setDescentRate(const float rate);
	void setPosition(const Vector2 newPosition);
	
	void update(void);
	void draw(void)const;

	friend std::ostream & operator<< (std::ostream &, const FishingRod &);
	friend std::istream & operator>> (std::istream &, FishingRod &);

};

inline float FishingRod::getDescentRate(void)const
{
	return this->descentRate;
}

inline void FishingRod::setDescentRate(const float rate)
{
	this->descentRate = rate;
}


#endif