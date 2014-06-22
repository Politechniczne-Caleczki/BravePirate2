#include "Ship.h"

Ship::Ship(const FloatingObject & floatingObject, const float speed, const float requiredEnergy,  const FishingRod fishingRod, const Cannon cannon):FloatingObject(floatingObject),
	speed(speed),
	requiredEnergy(fabs(requiredEnergy)),
	cannon(cannon),
	rod(fishingRod),
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
	if(Player::getInstance().getPlayerEnergy()>0)
	{
		if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && position.get_X()+size.get_X()<GraphicDevice::getWindowSize().get_X())
		{
			setPositionX(position.get_X()+  speed*Time::deltaTime());
			Player::getInstance().removePlayerEnery(requiredEnergy);
		}
		else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && position.get_X()>0)
		{
			setPositionX(position.get_X()- speed*Time::deltaTime());
			Player::getInstance().removePlayerEnery(requiredEnergy);
		}
	}

	checkCollisions();
	catchObjectUpdate();
	Vector2 o= getCenterPosition();
	rod.setPosition	  (Vector2 (cos (angle * PI / 180 )*( -size.get_Y()/2 ) + o.get_X() ,  sin( angle   *PI/180)* (-size.get_Y()/2 )+ o.get_Y() ));
	cannon.setPosition(Vector2 (cos (angle * PI / 180 )*(  size.get_Y()/2 ) + o.get_X() ,  sin((angle+3)*PI/180)* ( size.get_Y()/2 )+ o.get_Y() ));
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
			case cannonPowerBonus:
				{
					cannon.setPower(cannon.getPower() * bonus->getValue());					
				}break;
			case scoreBonus:
				{
					Player::getInstance().addScor((int)bonus->getValue());
				}break;

		}
		Player::getInstance().addScor((int)bonus->getValue());
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
		" "<<s.size<<" "<<s.textureName<<std::endl<<s.rod<<std::endl<< s.cannon<<std::endl;
}

std::istream & operator>> (std::istream &w, Ship &s)
{
	w>>s.angle>>s.back>>s.front>>s.position>>s.size>>s.textureName>>s.rod>>s.cannon;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}
