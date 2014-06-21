#ifndef Button_h
#define Button_h
#pragma once
#include "GraphicDevice.h"
#include "Ship.h"
#include "InstantionManager.h"
#include "Interface.h"

struct Container 
{
	Ship *ship;
	Sea *sea;
	Time *time;
	InstantionManager<Barrel> *barrels;
	InstantionManager<Fish> *fishes;
	void free()
	{
			if(ship!=NULL)		 delete ship;
			if(sea !=NULL)		 delete sea;
			if(time != NULL)     delete time;
			if(barrels!=NULL)	 delete barrels;
			if(fishes !=NULL)	 delete fishes;		
	}
};


class Button
{
private:
	SDL_Texture * textureActive;
	SDL_Texture * textureInactive;
	Vector2 position;
	bool active, available;
	int ( * _action ) (Container *);
	Container * cointainer;
public:
	Button(const bool active, const bool available, const Vector2 position, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (Container *), Container *);
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

#endif