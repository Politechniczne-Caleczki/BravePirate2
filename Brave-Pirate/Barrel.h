#pragma once
#include "FloatingObject.h"


class Barrel : public FloatingObject
{
private:
	float health, speed, damage;	

public:
	Barrel(void);
	Barrel(const FloatingObject floatingObject, const float health, const float speed, const float damage);
	~Barrel(void);

	void decreaseHealth(const float decreaseValue);
	void update();
	void onCollision(const float);
	void onCollision(void);
	const float getDamage()const;
	bool isDestroed()const;

};
