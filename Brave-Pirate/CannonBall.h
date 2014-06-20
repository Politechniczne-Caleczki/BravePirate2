#pragma once
#include "GameObject.h"
#include "Time.h"
#include "Sea.h"
#include "Player.h"
#include "Barrel.h"


class CannonBall : public GameObject
{
private:
	float speed, 		  
		  strikingPower, 
		  startTime, 
		  tcos, 
		  tsin;
	Vector2 posZero;

public:
	CannonBall(const Vector2 , const Vector2 , const float , const std::string , const float , const float);
	~CannonBall(void);

	void update(void);
	float getPower();
};

inline float CannonBall::getPower()
{
	return strikingPower;
}
