#ifndef Desert_h
#define Desert_h
#pragma once
#include "GameObject.h"
#include "Time.h"

class Desert: public GameObject
{
private: 
	float speed;
	static  Vector2 size; 
	static float delta;
public:
	static float shift, level, waveHeight;
	Desert(const Vector2 , const Vector2, const float, const std::string, float);
	~Desert(void);

	void draw(void)const;
	void update(void);
	static float getWaveHeight(const float );
	static float getDelta();

	friend std::ostream & operator<< (std::ostream &, const Desert &);
	friend std::istream & operator>> (std::istream &, Desert &);
};

inline float Desert::getWaveHeight(const float x)
{
	return level + waveHeight/2+ 20*sin((x-Desert::shift)/40);
}

inline float Desert::getDelta()
{
	return  Desert::shift - Desert::delta;
}
#endif