#include "Delay.h"

//Constructors and destructors

Delay::Delay(const float interval):delayTime(interval), isredy(true), startTime(0)
{
}

Delay::~Delay(void)
{
}


//Functions


std::ostream & operator<< (std::ostream &w, const Delay &d)
{
	return w<<d.delayTime<<" "<<d.startTime<<" "<<d.isredy;
}
std::istream & operator>> (std::istream &w, Delay &d)
{
	w>>d.delayTime>>d.startTime>>d.isredy;
	return w;
}
