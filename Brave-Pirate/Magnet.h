#ifndef Magnet_h
#define Magnet_h
#pragma once
#include "GameObject.h"
#include "Time.h"

class Magnet: public GameObject
{
private:
	GameObject *catchObject;
	float descentRate,  descent;
	Vector2 positionOfCar;
	void checkCollisions(void);
public:
	Magnet(const Vector2 position, const Vector2 size, const float angle, const std::string, const float descentRate);
	
	GameObject *getCatchObject(void);
	float getDescentRate(void)const;
	void setDescentRate(const float rate);
	void setPosition(const Vector2 newPosition);
	
	void update(void);
	void draw(void)const;

	friend std::ostream & operator<< (std::ostream &, const Magnet &);
	friend std::istream & operator>> (std::istream &, Magnet &);

};

inline float Magnet::getDescentRate(void)const
{
	return this->descentRate;
}

inline void Magnet::setDescentRate(const float rate)
{
	this->descentRate = rate;
}


#endif