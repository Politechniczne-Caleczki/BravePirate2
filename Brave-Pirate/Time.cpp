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

void Time::pauseTimer()
{
	paused = true;
}

void Time::continueTime()
{
	paused = false;
}


std::ostream & operator<< (std::ostream &w, const Time &t)
{
	return w<<(int)t.interval<<" "<<(int)t.last<<" "<<t._deltaTime
		<<" "<<(int)t._gameTime<<std::endl<<std::endl;
}

std::istream & operator>> (std::istream &w, Time &t)
{
	SDL_RemoveTimer(t.myTimerID);
	w>>t.interval>>t.last>>t._deltaTime
		>>t._gameTime;
	t.myTimerID = SDL_AddTimer(t.interval, &t.increment ,NULL);
	return w;
}

float Time::_deltaTime = 0;
Uint32 Time::_gameTime = 0;
bool Time::paused = true;