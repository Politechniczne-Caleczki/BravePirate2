#include "Interface.h"


Interface::Interface(const Vector2 position,const Vector2 size,SDL_Texture *background):InterfaceObject(position,size), background(background){}


Interface::~Interface(void)
{
}


void Interface::addObject(InterfaceObject * interfaceObject)
{
	interfaceList.push_back(interfaceObject);
}


void Interface::update(){}
void Interface::draw()const
{
	GraphicDevice::drawTexture(background,position,size);

	for(InterfaceList::const_iterator iter = interfaceList.begin(); iter!=interfaceList.end();iter++)
		(*iter)->draw();
}