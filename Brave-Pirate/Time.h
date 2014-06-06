#pragma once
#include <SDL.h>

class Time
{
private:
	Uint32 last,  interval;
	static Uint32 _gameTime, increment(const Uint32 interval, void *param);
	static float _delay;	
	int myTimerID;

public:
	Time(void);
	Time(Uint32 interval);
	~Time(void);
	
	void update();
	static float delay();
	static Uint32 gameTime();
};

