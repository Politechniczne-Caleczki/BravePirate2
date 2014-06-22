#include "Time.h"

//Constructors and destructors
Time::Time(void):last(0), interval(10)
{
	myTimerID = SDL_AddTimer(interval, &increment ,this);
	if(myTimerID ==0)throw GameError("Error creating thread clock: ", SDL_GetError());
	srand (time(NULL));
}

Time::Time(const Uint32 interval):last(0), interval(interval)
{
	myTimerID = SDL_AddTimer(interval, &increment ,NULL);
	if(myTimerID ==0)throw GameError("Error creating thread clock: ", SDL_GetError());
	srand (time(NULL));
}

Time::~Time(void)
{
	SDL_RemoveTimer(myTimerID);
}

//Functions


float Time::_deltaTime = 0;
Uint32 Time::_gameTime = 0;

std::ostream & operator<< (std::ostream &w, const Time &t)
{
	return w<<t.interval<<" "<<t.last<<" "<<t._deltaTime
		<<" "<<t._gameTime<<" ";
}

std::istream & operator>> (std::istream &w, Time &t)
{
	SDL_RemoveTimer(t.myTimerID);
	w>>t.interval>>t.last>>t._deltaTime
		>>t._gameTime;
	t.myTimerID = SDL_AddTimer(t.interval, &t.increment ,NULL);
	return w;
}