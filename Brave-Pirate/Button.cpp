#include "Button.h"

//Constructors and destructors
Button::Button(const bool active, const bool available, const Vector2 position, const Vector2 size, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (Container *), Container * container)
	:
	active(active),
	available(available),
	position(position),
	size(size),
	textureInactive(textureInactive),
	textureActive(textureActive),
	_action(_action),
	cointainer(container)
{

}

Button::~Button(void)
{
}

//Functions
int Button::action(void)
{
	return _action(cointainer);
}

void Button::draw(void)const
{
	if(active)
		GraphicDevice::drawTexture(textureActive, position, size);
	else 
		GraphicDevice::drawTexture(textureInactive, position, size);
}
