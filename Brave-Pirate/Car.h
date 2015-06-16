#ifndef Car_h
#define Car_h
#pragma once
#include <iostream>
#include "FloatingObject.h"
#include "Gun.h"
#include "Magnet.h"
#include "Obstacle.h"
#include "Player.h"
#include "Wheel.h"

class Car: public FloatingObject
{
private:
	Gun gun;
	Magnet magnet;
	GameObject *catchObject;	
	Wheel frontWheel, backWheel;
	float speed, requiredEnergy;
	void catchObjectUpdate(void);
	void checkCollisions(void);
public:
	Car(const FloatingObject & floatingObject, const float, const float, const Magnet, const Gun, const std::string , const float );
	~Car(void);
		
	void update(void);
	void draw(void)const;

	friend std::ostream & operator<< (std::ostream &, const Car &);
	friend std::istream & operator>> (std::istream &, Car &);
};

#endif