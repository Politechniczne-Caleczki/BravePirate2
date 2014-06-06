#pragma once
#include "GameObject.h"
#include "Time.h"

class Sea: public GameObject
{
private: 
	float speed;
	static Vector2 position, scale; 
	static float shift;

public:
	Sea(void);
	Sea(const GameObject gameobject, float speed);
	~Sea(void);

	void draw(void)const;
	void update(void);
	static float getWaveHeight(const float x);
};



