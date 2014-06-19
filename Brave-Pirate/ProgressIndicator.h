#pragma once
#include "InterfaceObject.h"

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
	void setPercentageValue(const float);
	const float getValue()const;
	const float getPercentageValue()const;

	void setText(const string);
	const string getText()const;

	void setColor(const SDL_Color);
	const SDL_Color getColor()const;
};


inline const float ProgressIndicator::getValue()const
{
	return value;
}

inline const float ProgressIndicator::getPercentageValue()const
{
	return value/frame.w;
}

inline void ProgressIndicator::setText(const string text)
{
	this->text = text;
}

inline const string ProgressIndicator::getText()const
{
	return text;
}

inline const SDL_Color ProgressIndicator::getColor()const
{
	return color;
}

inline void ProgressIndicator::setColor(const SDL_Color)
{
	this->color = color;
}

inline void ProgressIndicator::setValue(const float value)
{
	if(value>=0)
	{
		this->value = value;
		if(this->value>frame.w)
			this->value=frame.w;

		fill.w = value;
	}
}

inline void ProgressIndicator::setPercentageValue(const float value)
{
	setValue(value/100 * frame.w);
}
