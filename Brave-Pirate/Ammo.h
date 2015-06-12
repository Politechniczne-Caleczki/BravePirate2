#ifndef Ammo_h
#define Ammo_h
#pragma once
#include "Desert.h"
#include "Player.h"
#include "Obstacle.h"


class Ammo : public GameObject
{
private:
	float speed, 		  
		  strikingPower, 
		  startTime, 
		  tcos, 
		  tsin;
	Vector2 posZero;

public:
	Ammo(const Vector2 , const Vector2 , const float , const std::string , const float , const float);
	~Ammo(void);

	void update(void);
	float getPower();

	friend std::ostream & operator<< (std::ostream &, const Ammo &);
	friend std::istream & operator>> (std::istream &, Ammo &);
};

inline float Ammo::getPower()
{
	return strikingPower;
}

#endif
