#include "Ship.h"

Ship::Ship(const FloatingObject & floatingObject):FloatingObject(floatingObject),
	cannon(angle,1,position + Vector2(145,-75),1),
	rod(Vector2(100,300), Vector2(15,20), 0, "hook.png",0.08,200),
	catchObject(NULL){}

Ship::~Ship(void){}

//Functions


void Ship::draw(void)const
{
	cannon.draw();
	FloatingObject::draw();	
}

void Ship::lateDraw(void)const
{
	rod.draw();
}

void Ship::update(void)
{	
	checkCollisions();
	catchObjectUpdate();

	Vector2 o(size.get_X()/2, size.get_Y()/2);
	rod.setPosition(Vector2(cos(angle*PI/180)*(-75)+position.get_X()+o.get_X(),sin(angle*PI/180)*(-75)+position.get_Y()+o.get_Y()));
	cannon.setPosition(Vector2(cos(angle*PI/180)*(75)+position.get_X()+o.get_X(),sin((angle+3)*PI/180)*(75)+position.get_Y()+o.get_Y()));
	cannon.setAngle(-angle);

	cannon.update();
	rod.update();
	
	FloatingObject::update();	
}

void Ship::catchObjectUpdate(void)
{
	if((catchObject=rod.getCatchObject())!=NULL)
	{
		BonusObject *bonus = static_cast<BonusObject*>(catchObject);		
		switch(bonus->getType())
		{
			case energyFish:
				{
					Player::getInstance().addPlayerEnery(bonus->getValue());
				}break;
			case rodSpeedBonus:
				{
					rod.setDescentRate(rod.getDescentRate()* bonus->getValue());
				}break;
			case cannonSpeedBonus:
				{
					cannon.setInterval(Delay(cannon.getInterval().getDelay()* bonus->getValue()));
				}break;
			case healthShipBonus:
				{
					Player::getInstance().addShipHealth(bonus->getValue());
				}break;
		}


		delete catchObject;
		catchObject = NULL;
	}
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

std::ostream & operator<< (std::ostream &w, const Ship &s)
{
	return w<<s.angle<<" "<<s.back<<" "<<s.front<<" "<<s.position<<
		" "<<s.size<<" "<<s.textureName<<" \n"<< s.cannon<<" \n"<<s.rod<<std::endl;
}

std::istream & operator>> (std::istream &w, Ship &s)
{
	w>>s.angle>>s.back>>s.front>>s.position>>s.size>>s.textureName>>s.cannon>>s.rod;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}
