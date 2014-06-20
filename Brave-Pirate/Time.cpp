#include "Time.h"

//Constructors and destructors
Time::Time(void):last(0), interval(10)
{
	myTimerID = SDL_AddTimer(interval, &increment ,this);
	srand (time(NULL));
}

Time::Time(const Uint32 interval):last(0), interval(interval)
{
	myTimerID = SDL_AddTimer(interval, &increment ,NULL);
	srand (time(NULL));
}

Time::~Time(void)
{
	SDL_RemoveTimer(myTimerID);
}

//Functions


float Time::_deltaTime = 0;
Uint32 Time::_gameTime = 0;