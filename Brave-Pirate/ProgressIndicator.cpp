#include "ProgressIndicator.h"


ProgressIndicator::ProgressIndicator(const Vector2 position,const Vector2 size, const SDL_Color color):InterfaceObject(position,size),color(color), value(0), text("")
{
	frame.x = (int)position.get_X();
	frame.y = (int)position.get_Y();
	frame.w = (int)size.get_X();
	frame.h = (int)size.get_Y();
	fill = frame;
	fill.w = value;
}

ProgressIndicator::ProgressIndicator(const Vector2 position,const Vector2 size, const string text, const SDL_Color color):InterfaceObject(position,size),text(text),color(color), value(0)
{
	frame.x = (int)position.get_X();
	frame.y = (int)position.get_Y();
	frame.w = (int)size.get_X();
	frame.h = (int)size.get_Y();
	fill = frame;
	fill.w = value;
}

ProgressIndicator::ProgressIndicator(const Vector2 position,const Vector2 size, const SDL_Color color, const float value):InterfaceObject(position,size), color(color),value(value), text("")
{
	frame.x = (int)position.get_X();
	frame.y = (int)position.get_Y();
	frame.w = (int)size.get_X();
	frame.h = (int)size.get_Y();
	fill = frame;	

	if(this->value>frame.w)
		this->value=frame.w;

	fill.w = value;
}

ProgressIndicator::ProgressIndicator(const Vector2 position,const Vector2 size, const string text, const SDL_Color color, const float value):InterfaceObject(position,size), text(text), color(color),value(value)
{
	frame.x = (int)position.get_X();
	frame.y = (int)position.get_Y();
	frame.w = (int)size.get_X();
	frame.h = (int)size.get_Y();
	fill = frame;	

	if(this->value>frame.w)
		this->value=frame.w;

	fill.w = value;
}

ProgressIndicator::~ProgressIndicator(void){}

void ProgressIndicator::setValue(const float value)
{
	if(value>=0)
	{
		this->value = value;
		if(this->value>frame.w)
			this->value=frame.w;

		fill.w = value;
	}
}


const float ProgressIndicator::getValue()const{return value;}
void ProgressIndicator::draw()const
{
	SDL_SetRenderDrawColor(GraphicDevice::getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(GraphicDevice::getRenderer(),&fill);
	SDL_SetRenderDrawColor(GraphicDevice::getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(GraphicDevice::getRenderer(),&frame);
	GraphicDevice::drawText(text,GraphicDevice::getColor(0,0,0,255),Vector2(position.get_X()+3, position.get_Y()) ,size.get_Y());

}

void ProgressIndicator::update(){}

