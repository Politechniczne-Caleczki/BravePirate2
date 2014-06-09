#include "FishingRod.h"

//Constructors and destructors
FishingRod::FishingRod(const GameObject gameObject, const float descentRate, const float maxDepth, const Vector2 position):
descentRate(fabs(descentRate)),
	maxDepth(fabs(maxDepth)),
	GameObject(gameObject),
	descent(1)
{
	this->position = position;
}

//Getters and setters
float FishingRod::getDescentRate(void)const
{
	return this->descentRate;
}

float FishingRod::getMasDepth(void)const
{
	return this->maxDepth;
}
void FishingRod::setDescentRate(const float rate)
{
	this->descentRate = rate;
}

void FishingRod::setMaxDepth(const float depth)
{
	this->maxDepth = depth;
}

void FishingRod::setPosition(const Vector2 newPosition)
{
	this->positionOfShip = newPosition;
}

//Functions
void FishingRod::update(void)
{
	for(Lista::iterator iter = fishesArrayPointer.begin(); iter != fishesArrayPointer.end(); iter++)
	{
	}

	GameObject::update();
	position.set_X( (position.get_X()+positionOfShip.get_X())/2);
	position.set_Y( (position.get_Y()+positionOfShip.get_Y())/2+descent+100);
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] && position.get_Y()<500)
	{
		descent+=1*descentRate;
	}
	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && position.get_Y()>380)
	{
		descent-=1*descentRate;
	}
}

void FishingRod::draw(void)const
{
	SDL_RenderDrawLine(GraphicDevice::getRenderer(),positionOfShip.get_X(),positionOfShip.get_Y(),position.get_X(),position.get_Y());
	GraphicDevice::drawTexture(texture,Vector2(position.get_X()-10,position.get_Y()), Vector2(15,20));
}