#pragma once
#include "Time.h"

class Delay
{
private:
	float delayTime, startTime;
	bool isredy;

public:
	Delay(const float interval);
	~Delay(void);

	void setDealy(const float interval);

	void update(void);
	bool idRedy(void)const;
	void Start(void);
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

inline void Delay::setDealy(const float interval)
{
	this->delayTime = interval;
}
