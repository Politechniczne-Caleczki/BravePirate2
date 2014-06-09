#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GraphicDevice.h"
#include "GameStateManager.h"
#include "Button.h"
#include "Textures.h"

class Menu
{
private:
	Button **buttonList;
	SDL_Texture * background;
	int selected;
	SDL_Event e;
	bool keyPressed;

public:
	Menu(SDL_Texture * background);
	~Menu(void);

	int update(void);
	void draw(void)const;
};