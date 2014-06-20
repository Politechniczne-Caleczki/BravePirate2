#include "Button.h"

//Constructors and destructors
Button::Button(const bool active, const bool available, const Vector2 position, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (Container *), Container * container)
	:
	active(active),
	available(available),
	position(position),
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
		GraphicDevice::drawTexture(textureActive, position, Vector2(244,100));
	else 
		GraphicDevice::drawTexture(textureInactive, position, Vector2(244,100));
}
