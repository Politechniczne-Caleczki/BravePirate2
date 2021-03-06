#ifndef Button_h
#define Button_h
#pragma once
#include "GraphicDevice.h"
#include "Car.h"
#include "InstanceManager.h"
#include "Interface.h"
#include "Vector2.h"

struct Container 
{
	Car *ship;
	Desert *sea;
	Time *time;
	InstanceManager<Obstacle> *barrels;
	InstanceManager<Metal> *fishes;
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
	Vector2 position, size;
	bool active, available;
	int ( * _action ) (Container *);
	Container * cointainer;
public:
	Button(const bool active, const bool available, const Vector2 position, const Vector2 size, SDL_Texture * textureInactive, SDL_Texture * textureActive, int ( * _action ) (Container *), Container *);
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