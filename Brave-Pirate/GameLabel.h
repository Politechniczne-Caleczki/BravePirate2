#pragma once
#include "InterfaceObject.h"

class GameLabel : public InterfaceObject
{
private:
	string text;
	SDL_Color color;
	float textSize;
public:
	GameLabel(const string, const SDL_Color, const Vector2 ,const float);
	~GameLabel(void);

	void update();
	void draw()const;
	const string getText()const;
	void setText(const string);
	void setColor(const SDL_Color);
	const SDL_Color getColor()const;
};

inline void GameLabel::setText(const string text)
{
	this->text = text;
}
inline const string GameLabel::getText()const
{
	return text;
}
inline const SDL_Color GameLabel::getColor()const
{
	return color;
}
inline void GameLabel::setColor(const SDL_Color)
{
	this->color = color;
}

