#include "Time.h"

//Constructors and destructors
Time::Time(void):last(0), interval(10)
{
	myTimerID = SDL_AddTimer(interval, &increment ,this);
}

Time::Time(const Uint32 interval):last(0), interval(interval)
{
	myTimerID = SDL_AddTimer(interval, &increment ,NULL);
}

Time::~Time(void)
{
	SDL_RemoveTimer(myTimerID);
}

//Functions

void Time::update()
{
	Time::_delay = (float)(Time::_gameTime - last);
	last =Time::_gameTime;
}

float Time::delay()
{
	return _delay;
}

Uint32 Time::gameTime()
{
	return _gameTime;
}

Uint32 Time::increment(Uint32 interval, void *param)
{
	Time::_gameTime += interval;
	return interval;
}

float Time::_delay = 0;
Uint32 Time::_gameTime = 0;