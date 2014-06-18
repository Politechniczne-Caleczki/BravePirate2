#include "Barrel.h"

//Constructors and destructors

Barrel::Barrel(const FloatingObject & floatingObject, const float health, const float speed, const float damage):
	FloatingObject(floatingObject), 
	health(fabs(health)),
	speed(fabs(speed)),
	damage(fabs(damage))
{
}

Barrel::~Barrel(void)
{
	FloatingObject::~FloatingObject();
}

//Functions
void Barrel::decreaseHealth(const float decreaseValue)
{
	this->health -= fabs(decreaseValue);
	if(health<=0)
	{
		_isDestroyed=true;		
	}
}

void Barrel::update()
{		
	FloatingObject::setPositionX(position.get_X()-speed);
	FloatingObject::update();	
}

void Barrel::onCollision(const float power)
{
	health-=power;

	if(health<=0)
		onCollision();
}


