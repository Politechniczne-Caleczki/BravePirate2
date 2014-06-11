#include "FishingRod.h"

//Constructors and destructors
FishingRod::FishingRod(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const float descentRate, const float maxDepth):
	descentRate(fabs(descentRate)),
	maxDepth(fabs(maxDepth)),
	GameObject(position,size,angle,texture),
	descent(1){}

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
	this->position.set_X(newPosition.get_X());
	this->position.set_Y( (position.get_Y()+newPosition.get_Y())/2+descent);
}

//Functions
void FishingRod::update(void)
{
	for(Lista::iterator iter = fishesArrayPointer.begin(); iter != fishesArrayPointer.end(); iter++)
	{
		if(onCollision(*(*iter)))
			static_cast<Fish*>(*iter)->cought();
		if(static_cast<Fish*>(*iter)->getCought()){
			(*iter)->setPosition(position);
			if(descent<=0)
				static_cast<Fish*>(*iter)->onCollision();
		}
	}

	GameObject::update();
	
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] && position.get_Y()<550)
	{
		descent+=1*descentRate;
	}

	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && position.get_Y()>positionOfShip.get_Y())
	{
		descent-=1*descentRate;
	}
}

void FishingRod::draw(void)const
{
	SDL_RenderDrawLine(GraphicDevice::getRenderer(),positionOfShip.get_X(),positionOfShip.get_Y(),position.get_X(),position.get_Y());
	GraphicDevice::drawTexture(texture,Vector2(position.get_X()-10,position.get_Y()), size);
}