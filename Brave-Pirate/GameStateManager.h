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
	GameStateManager(const int state);

	void setGameState(int state);
	int getGameState(void)const;

	int update(void);
};

//Getters and setters
inline int GameStateManager::getGameState(void)const
{
	return gameState;
}

inline void GameStateManager::setGameState(int state)
{
	gameState=state;
}