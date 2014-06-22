#ifndef Cannon_h
#define Cannon_h
#pragma once
#include "CannonBall.h"
#include "Delay.h"

using namespace std;

class Cannon
{
private:
	
	float angle, power, requiredEnergy;
	Vector2 position;
	Delay interval; 
	list<CannonBall> cannonBalls;
public:
	Cannon(const float, const float, const Vector2,const Delay, float);
	~Cannon(void);

	void setAngle(const float);
	void setPosition(const Vector2);
	void setInterval(const Delay);
	const Delay & getInterval()const;

	void setPower(const float);
	const float getPower()const;

	void update(void);
	void draw(void)const;
	void fire(void);

	friend std::ostream & operator<< (std::ostream &, const Cannon &);
	friend std::istream & operator>> (std::istream &, Cannon &);
};

inline void Cannon::setPower(const float power)
{
	this->power = power;
}

inline const float Cannon::getPower()const
{
	return power;
}

inline void Cannon::setAngle(const float angle)
{
	this->angle = angle;
}

inline void Cannon::setPosition(const Vector2 position)
{
	this->position = position;
}

inline void Cannon::setInterval(const Delay interval)
{
	this->interval = interval;
}

inline const Delay & Cannon::getInterval()const
{
	return interval;
}

#endif

