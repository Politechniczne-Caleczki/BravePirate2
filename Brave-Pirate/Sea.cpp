#include "Sea.h"
#include "Time.h"

//Constructors and destructors
Sea::Sea(void)
{
}

Sea::Sea(const GameObject gameobject, float speed):	GameObject(gameobject),	speed(speed)
{
	Sea::position = GameObject::position;
	Sea::scale = GameObject::scale;
}

Sea::~Sea(void)
{
}

//Functions
void Sea::draw(void)const
{
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + shift , position.get_Y()), scale); 
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + scale.get_X() +shift , position.get_Y()), scale); 
}

void Sea::update(void)
{	
	Sea::shift -= Time::delay()*speed;
	Sea::shift = (int)Sea::shift%(int)scale.get_X();
}


float Sea::getWaveHeight(const float x)
{
	return Sea::position.get_Y()+ Sea::scale.get_Y()/2+ 20*sin((x-Sea::shift)/40);
}

Vector2 Sea::position = Vector2(0,0);
Vector2 Sea::scale = Vector2(0,0);
float Sea::shift = 0;