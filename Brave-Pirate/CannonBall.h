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
	CannonBall(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const float speed, const float strikingDistance, const float strikingPower);
	~CannonBall(void);

	void update(void);
	float getPower();
};

inline float CannonBall::getPower()
{
	return strikingPower*strikingDistance;
}
