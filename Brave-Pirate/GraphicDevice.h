#pragma once
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ConstantAndDefinitions.h"

class GraphicDevice
{
private:	
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::string windowName; 
	Vector2 windowPosition, windowSize;
	TTF_Font *font;
	void setWindow(void);	
	~GraphicDevice(void);
	GraphicDevice(void);
	static GraphicDevice * instance;
public:
	static GraphicDevice & getInstance();

	void setWindowSize(const Vector2 size);
	void setWindowPosition(const Vector2 position);
	void setWindowName(const std::string name);
	
	static SDL_Renderer* getRenderer(void);
	static Vector2 getWindowSize(void);

	static void drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size);
	static void drawTexture(SDL_Texture *texture,const Vector2 position,const Vector2 size, float angle);
	static void drawText(const std::string text,const SDL_Color textColor,const  Vector2 position,const float size);
	static void begin(void);
	static void end(void);
	static const SDL_Color getColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a);

	static void free();
};


inline GraphicDevice & GraphicDevice::getInstance()
{
	if(instance==NULL)	
		instance = new GraphicDevice();	

	return *instance;
}

inline SDL_Renderer* GraphicDevice::getRenderer()
{
	return getInstance().renderer;//error
}

inline Vector2 GraphicDevice::getWindowSize()
{
	return getInstance().windowSize;
}

//Functions
inline void GraphicDevice::begin()
{
	SDL_RenderClear(getInstance().getRenderer());
}

inline void GraphicDevice::end()
{
	SDL_RenderPresent(getInstance().getRenderer());
}

