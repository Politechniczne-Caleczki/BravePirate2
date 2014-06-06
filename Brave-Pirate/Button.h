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
	~Button(void);

	bool getActive(void)const;
	bool getAvailability(void)const;
	void setActive(bool active);
	void setAvailability(bool available);


	void draw(void)const;
	int action(void);
};