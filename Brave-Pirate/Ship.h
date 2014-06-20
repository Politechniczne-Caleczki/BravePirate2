#pragma once
#include "FloatingObject.h"
#include "Cannon.h"
#include "FishingRod.h"
#include "Barrel.h"
#include "Player.h"

class Ship: public FloatingObject
{
private:
	Cannon cannon;
	FishingRod rod;
	GameObject *catchObject;
	void catchObjectUpdate(void);
	void checkCollisions(void);
public:
	Ship(const FloatingObject & floatingObject);
	~Ship(void);
		
	void update(void);
	void draw(void)const;
	void lateDraw(void)const;
};
