#ifndef Menu_h
#define Menu_h
#pragma once
#include <list>
#include "GraphicDevice.h"
#include "GameStateManager.h"
#include "Button.h"

class Menu
{
	typedef std::list<Button> ButtonList;
private:
	ButtonList buttonList;
	ButtonList::iterator buttonIterator; 
	SDL_Texture * background;
	SDL_Event e;
	bool keyPressed;
public:
	Menu(SDL_Texture * background);
	~Menu(void);

	int update(void);
	void draw(void)const;
	void addButton(const Button &);
};

#endif