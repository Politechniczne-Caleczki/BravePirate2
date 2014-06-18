#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GraphicDevice.h"
#include "Vector2.h"

class Button
{
private:
	SDL_Texture * textureActive;
	SDL_Texture * textureInactive;
	Vector2 position;
	bool active, available;
	int ( * _action ) (void);

public:
	Button(const bool active, const bool available, const Vector2 position, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (void));
	~Button();
	inline const bool getActive(void)const;
	inline const bool getAvailability(void)const;
	inline void setActive(bool active);
	inline void setAvailability(bool available);


	void draw(void)const;
	int action(void);
};

//Getters and setters
inline const bool Button::getActive(void)const
{
	return active;
}

inline const bool Button::getAvailability(void)const
{
	return available;
}

inline void Button::setActive(bool active)
{
	this->active = active;
}

inline void Button::setAvailability(bool available)
{
	available = available;
}