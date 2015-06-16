#pragma once
#include "GameObject.h"
#include "Desert.h"

class Wheel :public GameObject
{
private:
	float circuit;
public:
	Wheel(GameObject);
	~Wheel();

	const float getCircuit()const;
	void draw(void)const;
	void update(void);
};

inline const float Wheel::getCircuit()const
{
	return this->circuit;
}

