#pragma once
#include "BonusObject.h"
#include "Fish.h"
#include "Time.h"
class Fish: public BonusObject
{
private:
	
public:
	Fish(const Vector2, const Vector2, const float, const std::string , float, float);
	~Fish(void);
	void update(void);
};
