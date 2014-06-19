#include "Ship.h"
//Constructors and destructors
//Ship::Ship(void):rod(new FloatingObject(new  GameObject(Vector2(100,300), Vector2(150,200), 0, Textures::getTexture("hook.png")), Vector2(100,145), Vector2(100, 145)),0.5,200, Vector2(60,100))
//{
//}

Ship::Ship(const FloatingObject & floatingObject):FloatingObject(floatingObject),
	cannon(angle,1,position + Vector2(145,-75)),
	rod(Vector2(100,300), Vector2(15,20), 0, Textures::getTexture("hook.png"),0.5,200),
	catchObject(NULL){}

Ship::~Ship(void){}

//Functions


void Ship::draw(void)const
{
	cannon.draw();
	FloatingObject::draw();
	rod.draw();
}

void Ship::update(void)
{	
	checkCollisions();
	if((catchObject=rod.getCatchObject())!=NULL)
	{
		delete catchObject;
		catchObject = NULL;
	}

	Vector2 o(size.get_X()/2, size.get_Y()/2);
	rod.setPosition(Vector2(cos(angle*PI/180)*(-75)+position.get_X()+o.get_X(),sin(angle*PI/180)*(-75)+position.get_Y()+o.get_Y()));
	cannon.setPosition(Vector2(cos(angle*PI/180)*(75)+position.get_X()+o.get_X(),sin((angle+3)*PI/180)*(75)+position.get_Y()+o.get_Y()));
	cannon.setAngle(-angle);

	cannon.update();
	rod.update();
	FloatingObject::update();	
}

void Ship::checkCollisions(void)
{
	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end(); iter++)
	{		
		if(onCollision(*(*iter)))
		{
			(*iter)->onCollision();		
			Player::getInstance().removeShipHealth(static_cast<Barrel*>(*iter)->getDamage());
		}
	}
}

