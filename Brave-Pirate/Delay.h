#ifndef Delay_h
#define Delay_h
#pragma once
#include "Time.h"
#include <iostream>
class Delay
{
private:
	float delayTime, startTime;
	bool isredy;

public:
	Delay(const float interval);
	~Delay(void);

	void setDelay(const float interval);
	const float getDelay()const;

	void update(void);
	bool idRedy(void)const;
	void Start(void);

	friend std::ostream & operator<< (std::ostream &, const Delay &);
	friend std::istream & operator>> (std::istream &, Delay &);
};


inline bool Delay::idRedy(void)const
{
	return isredy;
}

inline void Delay::Start(void)
{
	isredy = false;
	startTime = (float)Time::gameTime();
}

inline void Delay::setDelay(const float interval)
{
	this->delayTime = interval;
}

inline const float Delay::getDelay()const
{
	return delayTime;
}

inline void Delay::update(void)
{
	if(!isredy)
		if(startTime+delayTime < (float)Time::gameTime())
			isredy = true;
}

#endif