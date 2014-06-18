#pragma once
#include "GameObject.h"
#include "Time.h"


class Sea: public GameObject
{
private: 
	float speed;
	static Vector2 position, size; 
	static float shift;

public:
	Sea(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, float speed);
	~Sea(void);

	void draw(void)const;
	void update(void);
	static float getWaveHeight(const float x);
};

inline float Sea::getWaveHeight(const float x)
{
	return Sea::position.get_Y()+ Sea::size.get_Y()/2+ 20*sin((x-Sea::shift)/40);
}
