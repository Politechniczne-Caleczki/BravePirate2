#pragma once
#include "FloatingObject.h"
#include "Cannon.h"
#include "FishingRod.h"
#include "Barrel.h"

class Ship: public FloatingObject
{
private:
	float shipHealth, pirateHealth;
	int points;
	Cannon cannon;
	FishingRod rod;

public:
	Ship(const FloatingObject & floatingObject,const float shipHealth,const float pirateHealth,const unsigned int points);
	~Ship(void);

	void changeShipHealth(const float health);
	void changePirateHealth(const float health);
	void addPoints(const int point);
	void addPoint(void);
	void update(void);
	void draw(void)const;

	const float getShipHealth()const;
	const float getPirateHealth()const;
	bool onCollision(GameObject &gameObject)const;
};