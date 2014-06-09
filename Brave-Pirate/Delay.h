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

