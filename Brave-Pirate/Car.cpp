#include "Car.h"

Car::Car(const FloatingObject & floatingObject, const float speed, const float requiredEnergy, const Magnet magnet, const Gun gun, const std::string wheelTexture, const float wheelSize) :FloatingObject(floatingObject),
speed(speed),requiredEnergy(fabs(requiredEnergy)),gun(gun),magnet(magnet),
frontWheel(Wheel(GameObject(this->front , Vector2(wheelSize, wheelSize), rand(), wheelTexture))),
backWheel(Wheel(GameObject(this->back, Vector2(wheelSize, wheelSize), rand(), wheelTexture))),
catchObject(NULL)
{}

Car::~Car(void){}

//Functions


void Car::draw(void)const
{
	gun.draw();
	FloatingObject::draw();	
	magnet.draw();
	frontWheel.draw();
	backWheel.draw();
}

void Car::update(void)
{
	if (Player::getInstance().getPlayerEnergy() > 0)
	{
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && position.get_X() + size.get_X() < GraphicDevice::getWindowSize().get_X())
		{
			float delta = speed * Time::deltaTime();
			setPositionX(position.get_X() + delta);
			frontWheel.setAngle(frontWheel.getAngle() + delta / frontWheel.getCircuit() * 360);
			backWheel.setAngle(backWheel.getAngle() + delta / backWheel.getCircuit() * 360);

			Player::getInstance().removePlayerEnery(requiredEnergy);
		}
		else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && position.get_X() > 0)
		{
			float delta = -speed * Time::deltaTime();
			setPositionX(position.get_X() +delta);
			frontWheel.setAngle(frontWheel.getAngle() + delta / frontWheel.getCircuit() * 360);
			backWheel.setAngle(backWheel.getAngle() + delta / backWheel.getCircuit() * 360);
			Player::getInstance().removePlayerEnery(requiredEnergy);
		}
	}

	checkCollisions();
	catchObjectUpdate();
	Vector2 o = getCenterPosition();
	magnet.setPosition(Vector2(cos(angle * PI / 180)*(-size.get_Y() / 2) + o.get_X(), sin(angle   *PI / 180)* (-size.get_Y() / 2) + o.get_Y()));
	gun.setPosition(Vector2(40 + cos(angle * PI / 180)*(size.get_Y() / 2) + o.get_X(), -30 + sin((angle + 3)*PI / 180)* (size.get_Y() / 2) + o.get_Y()));
	gun.setAngle(-angle);

	gun.update();
	magnet.update();

	frontWheel.setPosition(Vector2(front.get_X() + 50 * sin(-this->angle*PI / 180), front.get_Y() - frontWheel.getSize().get_X()));
	backWheel.setPosition(Vector2(back.get_X() + 50 * sin(-this->angle*PI / 180), back.get_Y() - backWheel.getSize().get_X()));
	frontWheel.update();
	backWheel.update();

	FloatingObject::update();
}

void Car::catchObjectUpdate(void)
{	
	if((catchObject=magnet.getCatchObject())!=NULL)
	{
		BonusObject *bonus = static_cast<BonusObject*>(catchObject);	
		switch(bonus->getType())
		{
			case energyBonus:
				{
					Player::getInstance().addPlayerEnery(bonus->getValue());
				}break;
			case magnetSpeedBonus:
				{
					magnet.setDescentRate(magnet.getDescentRate()* bonus->getValue());					
				}break;
			case gunSpeedBonus:
				{
					gun.setInterval(Delay(gun.getInterval().getDelay()* bonus->getValue()));					
				}break;
			case healthCarBonus:
				{
					Player::getInstance().addCarHealth(bonus->getValue());
				}break;
			case gunPowerBonus:
				{
					gun.setPower(gun.getPower() * bonus->getValue());					
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

void Car::checkCollisions(void)
{
	for(Lista::iterator iter = GameObject::cactosArrayPointer.begin(); iter!= GameObject::cactosArrayPointer.end(); iter++)
	{		
		if(onCollision(*(*iter)))
		{
			(*iter)->onCollision();		
			Player::getInstance().removeCarHealth(static_cast<Obstacle*>(*iter)->getDamage());
		}
	}
}

std::ostream & operator<< (std::ostream &w, const Car &s)
{
	return w<<s.angle<<" "<<s.back<<" "<<s.front<<" "<<s.position<<
		" "<<s.size<<" "<<s.textureName<<std::endl<<s.magnet<<std::endl<< s.gun<<std::endl;
}

std::istream & operator>> (std::istream &w, Car &s)
{
	w>>s.angle>>s.back>>s.front>>s.position>>s.size>>s.textureName>>s.magnet>>s.gun;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}
