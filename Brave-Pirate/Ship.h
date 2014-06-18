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
	GameObject *catchObject;
	void checkCollisions(void);
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

inline void Ship::changeShipHealth(const float health)
{
	this->shipHealth += health;
}

inline void Ship::changePirateHealth(const float health)
{
	this->shipHealth += health;
}

inline void Ship::addPoint(void)
{
	this->points++;
}

inline void Ship::addPoints(const int point)
{
	this->points += point;
}


inline const float Ship::getShipHealth()const
{
	return shipHealth;
}

inline const float Ship::getPirateHealth()const
{
	return pirateHealth;
}
