#include"GameStateManager.h"

//Constructors and destructors
GameStateManager::GameStateManager(const int state):gameState(state)
{
}


//Functions
int GameStateManager::update(void)
{
	SDL_PollEvent(&e);
	
	if((gameState == 2 || gameState == 3) && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])
	{
		Time::pauseTimer();
		gameState=1;
	}
	if(e.type == SDL_QUIT)
		gameState = 0;
	return gameState;
}