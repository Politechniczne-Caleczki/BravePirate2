#include "Delay.h"

//Constructors and destructors

Delay::Delay(const float interval):delayTime(interval), isredy(true), startTime(0)
{
}

Delay::~Delay(void)
{
}

//Getters and setters
void Delay::setDealy(const float interval)
{
	this->delayTime = interval;
}

//Functions
void Delay::update(void)
{
	if(!isredy)
		if(startTime+delayTime < (float)Time::gameTime())
			isredy = true;
}

bool Delay::idRedy(void)const
{
	return isredy;
}

void Delay::Start(void)
{
	isredy = false;
	startTime = (float)Time::gameTime();
}
