#include "Ship.h"
//Constructors and destructors
//Ship::Ship(void):rod(new FloatingObject(new  GameObject(Vector2(100,300), Vector2(150,200), 0, Textures::getTexture("hook.png")), Vector2(100,145), Vector2(100, 145)),0.5,200, Vector2(60,100))
//{
//}

Ship::Ship(const FloatingObject & floatingObject,const float shipHealth,const float pirateHealth,const unsigned int points):FloatingObject(floatingObject),
	shipHealth(fabs(shipHealth)), 
	pirateHealth(fabs(shipHealth)),
	points(points),
	cannon(angle,1,position + Vector2(145,-75)),
	rod(Vector2(100,300), Vector2(150,200), 0, Textures::getTexture("hook.png"),0.5,200)
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

void Ship::draw(void)const
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
	
	Vector2 o(size.get_X()/2, size.get_Y()/2);
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

bool Ship::onCollision(GameObject &gameObject)const
{
	return GameObject::onCollision(gameObject);
}


const float Ship::getShipHealth()const
{
	return shipHealth;
}

const float Ship::getPirateHealth()const
{
	return pirateHealth;
}

