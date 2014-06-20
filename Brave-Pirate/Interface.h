#pragma once
#include <SDL.h>
#include "InterfaceObject.h"
#include <list>
#include <cstddef>
#include "GraphicDevice.h"

using namespace std;
typedef std::list<InterfaceObject*> InterfaceList;

class Interface : public InterfaceObject
{
private:
	InterfaceList interfaceList;
	SDL_Texture *background;
public:
	Interface(const Vector2 ,const Vector2 ,SDL_Texture *background);
	~Interface(void);

	void update();
	void draw()const;

	void addObject(InterfaceObject *);
};

