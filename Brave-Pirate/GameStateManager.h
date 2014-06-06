#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GraphicDevice.h"
#include "Vector2.h"

class GameStateManager
{
private:
	SDL_Event e;
	int gameState;

public:	
	GameStateManager(void);
	GameStateManager(const int state);

	void setGameState(int state);
	int getGameState(void)const;

	int update(void);
};