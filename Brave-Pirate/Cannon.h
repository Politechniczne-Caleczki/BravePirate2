#pragma once
#include <list>
#include "CannonBall.h"
#include "Delay.h"
#include "Sea.h"

class Cannon
{
private:
	Delay interval;
	float angle, power;
	unsigned int requiredEnergy;
	Vector2 position; 
	std::list<CannonBall> cannonBalls;

public:
	Cannon(const float, const float, const Vector2, const unsigned int);
	~Cannon(void);

	void setAngle(const float);
	void setPosition(const Vector2);
	void setInterval(const Delay);
	const Delay & getInterval()const;

	void update(void);
	void draw(void)const;
	void fire(void);
};

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

