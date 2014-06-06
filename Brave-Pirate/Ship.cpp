#include "Ship.h"
//Constructors and destructors
Ship::Ship(void):rod(FloatingObject( GameObject(Vector2(100,300), Vector2(150,200), 0, Textures::getTexture("hook.png")), Vector2(100,145), Vector2(100, 145)),0.5,200, Vector2(60,100))
{
}

Ship::Ship(const FloatingObject floatingObject):
	FloatingObject(floatingObject),
	shipHealth(100), 
	pirateHealth(100),
	points(0),
	cannon(angle,1,floatingObject.getPosition()+Vector2(145,-75)),
	rod(FloatingObject( GameObject(Vector2(100,300), Vector2(150,200), 0, Textures::getTexture("hook.png")), Vector2(110,145), Vector2(160, 145)),0.5,200, Vector2(60,500))
{
}

Ship::~Ship(void)
{
}

//Functions
void Ship::changeShipHealth(const float health)
{
	this->shipHealth += health;
}

void Ship::changePirateHealth(const float health)
{
	this->shipHealth += health;
}

void Ship::addPoint(void)
{
	this->points++;
}

void Ship::draw(void)
{
	cannon.draw();
	FloatingObject::draw();
	rod.draw();
}

void Ship::update(void)
{
	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end(); iter++)
	{		
		if(onCollision(*(*iter)))
		{
			(*iter)->onCollision();		
			this->shipHealth-=  static_cast<Barrel*>(*iter)->getDamage();
		}
	}
	
	Vector2 o(scale.get_X()/2, scale.get_Y()/2);
	rod.setPosition(Vector2(cos(angle*PI/180)*(-75)+position.get_X()+o.get_X(),sin(angle*PI/180)*(-75)+position.get_Y()+o.get_Y()));
	cannon.setPosition(Vector2(cos(angle*PI/180)*(75)+position.get_X()+o.get_X(),sin((angle+3)*PI/180)*(75)+position.get_Y()+o.get_Y()));
	cannon.setAngle(-angle);
	cannon.update();
	rod.update();
	FloatingObject::update();	
}

void Ship::addPoints(const int point)
{
	this->points += point;
}


