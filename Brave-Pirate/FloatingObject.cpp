#include "FloatingObject.h"

//Constructors and destructors

FloatingObject::~FloatingObject(void)
{
	GameObject::~GameObject();
}

FloatingObject::FloatingObject(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, const Vector2 front, const Vector2 back):
GameObject(position,size,angle,textureName),front(front), back(back), difference((front.get_Y() + back.get_Y()) / 2){}

//Getters and setters
void FloatingObject::setPositionX(const float x)
{
	float v1 = position.get_X() - front.get_X();
	float v2 = position.get_X() - back.get_X();
	position.set_X(x);
	front.set_X(position.get_X() - v1);
	back.set_X(position.get_X() - v2);
}

void FloatingObject::setPositionY(void)
{
	front.set_Y(Sea::getWaveHeight(front.get_X()));
	back.set_Y(Sea::getWaveHeight(back.get_X()));
	position.set_Y(((front.get_Y() + back.get_Y()) / 2) - difference);
}

//Functions
void FloatingObject::update(void)
{			
	setPositionY();
	angle = back.angleDeg(front);	
	GameObject::update();
}

void FloatingObject::draw(void)const
{
	GraphicDevice::drawTexture(texture, position, size, angle);
}
