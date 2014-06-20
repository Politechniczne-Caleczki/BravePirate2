#include "FishingRod.h"

//Constructors and destructors
FishingRod::FishingRod(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, const float descentRate, const float maxDepth):
	descentRate(fabs(descentRate)),
	maxDepth(fabs(maxDepth)),
	GameObject(position,size,angle,textureName),
	descent(1),
	catchObject(NULL){}


//Getters and setters


void FishingRod::setPosition(const Vector2 newPosition)
{
	this->positionOfShip = newPosition;
	this->position.set_X(newPosition.get_X());
	this->position.set_Y( (position.get_Y()+newPosition.get_Y())/2+descent);
}

//Functions
void FishingRod::update(void)
{
	GameObject::update();

	if(catchObject==NULL)
	{
		checkCollisions();
	}else
	{
		catchObject->setPosition(position);
	}

	
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] && position.get_Y()<550)
	{
		descent+= Time::deltaTime() *descentRate;
	}

	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && position.get_Y()>positionOfShip.get_Y())
	{
		descent-=Time::deltaTime() *descentRate;
	}
}

void FishingRod::checkCollisions(void)
{
	for(Lista::iterator iter = fishesArrayPointer.begin(); iter != fishesArrayPointer.end(); iter++)
	{
		if(onCollision(*(*iter)))
		{
			catchObject = (*iter);
			fishesArrayPointer.erase(iter);
			break;
		}
	}
}

void FishingRod::draw(void)const
{
	SDL_RenderDrawLine(GraphicDevice::getRenderer(),positionOfShip.get_X(),positionOfShip.get_Y(),position.get_X(),position.get_Y());
	GraphicDevice::drawTexture(texture,Vector2(position.get_X()- size.get_X()/2,position.get_Y()), size);
	if(catchObject!=NULL)
		catchObject->draw();
}

GameObject * FishingRod::getCatchObject(void)
{
	if(descent<=0)
	{
		GameObject *gO = catchObject;
		catchObject=NULL;
		return gO;
	}
	
	return NULL;	
}

std::ostream & operator<< (std::ostream &w, const FishingRod &r)
{
	return w<<r.angle<<" "<<r.descent<<" "<<r.descentRate<<" "<<r.maxDepth
		<<" "<<r.position<<" "<<r.positionOfShip<<" "<<r.size<<" "<<r.textureName<<std::endl;

}

std::istream & operator>> (std::istream &w, FishingRod &r)
{
	w>>r.angle>>r.descent>>r.descentRate>>r.maxDepth>>r.position
		>>r.positionOfShip>>r.size>>r.textureName;
	r.texture = Textures::getTexture(r.textureName);
	return w;
}