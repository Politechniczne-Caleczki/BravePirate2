#ifndef Sea_h
#define Sea_h
#pragma once
#include "GameObject.h"
#include "Time.h"

class Sea: public GameObject
{
private: 
	float speed;
	static  Vector2 size; 
public:
	static float shift,  seaLevel , waveHeight;
	Sea(const Vector2 , const Vector2, const float, const std::string, float);
	~Sea(void);

	void draw(void)const;
	void update(void);
	static float getWaveHeight(const float );

	friend std::ostream & operator<< (std::ostream &, const Sea &);
	friend std::istream & operator>> (std::istream &, Sea &);
};

inline float Sea::getWaveHeight(const float x)
{
	return seaLevel + waveHeight/2+ 20*sin((x-Sea::shift)/40);
}
#endif