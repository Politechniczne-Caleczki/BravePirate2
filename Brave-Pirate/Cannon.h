#pragma once
#include <SDL_image.h>
#include <list>
#include "Vector2.h"
#include "CannonBall.h"
#include "Delay.h"
#include "Sea.h"
#include "Textures.h"

using namespace std;

class Cannon
{
private:
	Delay interval;
	float angle, power;
	Vector2 position; 
	list<CannonBall> cannonBalls;

public:
	Cannon(const float angle, const float power, const Vector2 position);
	~Cannon(void);

	void setAngle(const float angle);
	void setPosition(const Vector2 vector2);
	void setInterval(const Delay interval);

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

