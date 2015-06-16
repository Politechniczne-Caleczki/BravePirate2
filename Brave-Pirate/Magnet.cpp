#include "Magnet.h"

//Constructors and destructors
Magnet::Magnet(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, const float descentRate):
	descentRate(fabs(descentRate)),	
	GameObject(position,size,angle,textureName),
	descent(1),
	catchObject(NULL){}


//Getters and setters


void Magnet::setPosition(const Vector2 newPosition)
{
	this->positionOfShip = newPosition;
	this->position.set_X(newPosition.get_X());
	this->position.set_Y( (position.get_Y()+newPosition.get_Y())/2+descent);
}

//Functions
void Magnet::update(void)
{
	GameObject::update();

	if(catchObject==NULL)
	{
		checkCollisions();
	}else
	{
		catchObject->setPosition(position);
	}

	
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] && position.get_Y()+size.get_Y() < GraphicDevice::getWindowSize().get_Y())
	{
		descent+= Time::deltaTime() *descentRate;
	}

	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && position.get_Y()>positionOfShip.get_Y())
	{
		descent-=Time::deltaTime() *descentRate;
	}
}

void Magnet::checkCollisions(void)
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

void Magnet::draw(void)const
{
	SDL_RenderDrawLine(GraphicDevice::getRenderer(),(int)positionOfShip.get_X(), (int)positionOfShip.get_Y(),(int)position.get_X(), (int)position.get_Y());
	GraphicDevice::drawTexture(texture,Vector2(position.get_X()- size.get_X()/2,position.get_Y()), size);
	if(catchObject!=NULL)
		catchObject->draw();
}

GameObject * Magnet::getCatchObject(void)
{
	if(descent<=0)
	{
		GameObject *gO = catchObject;
		catchObject=NULL;
		return gO;
	}
	
	return NULL;	
}

std::ostream & operator<< (std::ostream &w, const Magnet &r)
{
	return w<<r.angle<<" "<<r.descent<<" "<<r.descentRate
		<<" "<<r.position<<" "<<r.positionOfShip<<" "<<r.size<<" "<<r.textureName<<std::endl;

}

std::istream & operator>> (std::istream &w, Magnet &r)
{
	w>>r.angle>>r.descent>>r.descentRate>>r.position
		>>r.positionOfShip>>r.size>>r.textureName;
	r.texture = Textures::getTexture(r.textureName);
	return w;
}