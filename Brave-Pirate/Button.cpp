#include "Button.h"

//Constructors and destructors
Button::Button(const bool active, const bool available, const Vector2 position, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (void)):
	active(active),
	available(available),
	position(position),
	textureInactive(textureInactive),
	textureActive(textureActive)
	
{
	this->_action = *_action;
}

Button::~Button(void)
{
	SDL_DestroyTexture(textureActive);
	SDL_DestroyTexture(textureInactive);
}

//Getters and setters
bool Button::getActive(void)const
{
	return active;
}

bool Button::getAvailability(void)const
{
	return available;
}

void Button::setActive(bool active)
{
	this->active = active;
}

void Button::setAvailability(bool available)
{
	available = available;
}

//Functions
int Button::action(void)
{
	return _action();
}

void Button::draw(void)const
{
	if(active)
		GraphicDevice::drawTexture(textureActive, position, Vector2(244,100));
	else 
		GraphicDevice::drawTexture(textureInactive, position, Vector2(244,100));
}
