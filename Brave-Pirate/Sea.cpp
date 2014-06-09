#include "Sea.h"



//Constructors and destructors

Sea::Sea(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, float speed):GameObject(position,size,angle,texture),speed(speed)
{
	Sea::position = GameObject::position;
	Sea::size = GameObject::size;
}

Sea::~Sea(void)
{
}

//Functions
void Sea::draw(void)const
{
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + shift , position.get_Y()), size); 
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + size.get_X() +shift , position.get_Y()), size); 
}

void Sea::update(void)
{	
	Sea::shift -= Time::delay()*speed;
	Sea::shift = (int)Sea::shift%(int)size.get_X();
}


float Sea::getWaveHeight(const float x)
{
	return Sea::position.get_Y()+ Sea::size.get_Y()/2+ 20*sin((x-Sea::shift)/40);
}

Vector2 Sea::position = Vector2(0,0);
Vector2 Sea::size = Vector2(0,0);
float Sea::shift = 0;