#ifndef Car_h
#define Car_h
#pragma once
#include <iostream>
#include "FloatingObject.h"
#include "Gun.h"
#include "Magnet.h"
#include "Obstacle.h"
#include "Player.h"

class Car: public FloatingObject
{
private:
	Gun cannon;
	Magnet rod;
	GameObject *catchObject;
	float speed, requiredEnergy;
	void catchObjectUpdate(void);
	void checkCollisions(void);
public:
	Car(const FloatingObject & floatingObject, const float, const float, const Magnet, const Gun);
	~Car(void);
		
	void update(void);
	void draw(void)const;
	void lateDraw(void)const;

	friend std::ostream & operator<< (std::ostream &, const Car &);
	friend std::istream & operator>> (std::istream &, Car &);
};

#endif