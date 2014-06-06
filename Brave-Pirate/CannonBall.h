#pragma once
#include "GameObject.h"
#include "Time.h"
#include "Sea.h"

class CannonBall : public GameObject
{
private:
	float speed, 
		strikingDistance, 
		strikingPower, 
		startTime, 
		tcos, 
		tsin;
	Vector2 posZero;

public:
	CannonBall(const GameObject gameObject, const float speed, const float strikingDistance, const float strikingPower);
	CannonBall(void);
	~CannonBall(void);

	void update(void);	
	float getPower();
};

