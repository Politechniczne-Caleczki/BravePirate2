#pragma once
#include "BonusObject.h"
#include "Time.h"

class Bonus:public BonusObject
{
private: 
	float depth;
public:
	Bonus(const Vector2, const Vector2, const float, const std::string , float, float, float);
	~Bonus(void);
	void update(void);
};

