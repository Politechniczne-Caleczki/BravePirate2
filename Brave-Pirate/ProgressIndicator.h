#pragma once
#include "InterfaceObject.h"
#include "GraphicDevice.h"

class ProgressIndicator:public InterfaceObject
{
private:
	float value;
	SDL_Rect frame, fill;
	SDL_Color color;
	string text;
public:
	ProgressIndicator(const Vector2 ,const Vector2, const SDL_Color color);
	ProgressIndicator(const Vector2 ,const Vector2, const SDL_Color color, const float);
	ProgressIndicator(const Vector2 ,const Vector2, const string , const SDL_Color color);
	ProgressIndicator(const Vector2 ,const Vector2, const string , const SDL_Color color, const float);
	~ProgressIndicator(void);

	void update();
	void draw()const;
	void setValue(const float);
	const float getValue()const;
};

