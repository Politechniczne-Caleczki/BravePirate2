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
	Ship(void);
	Ship(const FloatingObject floatingObject);
	~Ship(void);

	void changeShipHealth(const float health);
	void changePirateHealth(const float health);
	void addPoints(const int point);
	void addPoint(void);
	void update(void);
	void draw(void);
};