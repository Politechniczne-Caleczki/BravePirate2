#include "GameLabel.h"


GameLabel::GameLabel(const std::string text,const SDL_Color color, const Vector2 position, const float textSize):InterfaceObject(position,Vector2(0,0)), textSize(textSize), color(color), text(text)
{
}

GameLabel::~GameLabel(void)
{
}

void GameLabel::draw()const
{
	GraphicDevice::drawText(text, color,position,textSize);	
}

void GameLabel::update()
{
}