#ifndef Gun_h
#define Gun_h
#pragma once
#include "Ammo.h"
#include "Delay.h"

using namespace std;

class Gun
{
private:
	
	float angle, power, requiredEnergy;
	Vector2 position;
	Delay interval; 
	list<Ammo> ammos;
public:
	Gun(const float, const float, const Vector2,const Delay, float);
	~Gun(void);

	void setAngle(const float);
	void setPosition(const Vector2);
	void setInterval(const Delay);
	const Delay & getInterval()const;

	void setPower(const float);
	const float getPower()const;

	void update(void);
	void draw(void)const;
	void fire(void);

	friend std::ostream & operator<< (std::ostream &, const Gun &);
	friend std::istream & operator>> (std::istream &, Gun &);
};

inline void Gun::setPower(const float power)
{
	this->power = power;
}

inline const float Gun::getPower()const
{
	return power;
}

inline void Gun::setAngle(const float angle)
{
	this->angle = angle;
}

inline void Gun::setPosition(const Vector2 position)
{
	this->position = position;
}

inline void Gun::setInterval(const Delay interval)
{
	this->interval = interval;
}

inline const Delay & Gun::getInterval()const
{
	return interval;
}

#endif

