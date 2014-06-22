#ifndef Time_h
#define Time_h
#pragma once
#include <SDL.h>
#include <time.h>  
#include <iostream>
class Time
{
private:
	Uint32 last,  interval;
	static Uint32 _gameTime, increment(const Uint32 interval, void *param);
	static float _deltaTime;	
	int myTimerID;
	static bool paused;

public:
	Time(void);
	Time(Uint32 interval);
	~Time(void);
	
	void update();
	static float deltaTime();
	static Uint32 gameTime();

	friend std::ostream & operator<< (std::ostream &, const Time &);
	friend std::istream & operator>> (std::istream &, Time &);

	static void pauseTimer();
	static void continueTime();
};

inline void Time::update()
{
	Time::_deltaTime = (float)(Time::_gameTime - last);
	last =Time::_gameTime;
}

inline float Time::deltaTime()
{
	return _deltaTime;
}

inline Uint32 Time::gameTime()
{
	return _gameTime;
}

inline Uint32 Time::increment(Uint32 interval, void *param)
{
	if(!paused)
		Time::_gameTime += interval;
	return interval;
}

#endif