#ifndef GraphicDevice_h
#define GraphicDevice_h
#pragma once
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ConstantAndDefinitions.h"
#include "GameError.h"

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
	void deletePointerObject();
	void initPointerObject();
	void loadWindowsSetting();
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
	{
		try
		{
			instance = new GraphicDevice();	
		}
		catch(GameError & error)
		{
			error.generateErrorLog(errorFile);
			throw;
		}
		catch( ... )
		{
			throw;
		}
	}
	return *instance;
}

inline SDL_Renderer* GraphicDevice::getRenderer()
{
	return getInstance().renderer;
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

inline void GraphicDevice::drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size)
{
	SDL_Rect rect;
	rect.x = (int)position.get_X();
	rect.y = (int)position.get_Y();
	rect.w = (int)size.get_X();
	rect.h = (int)size.get_Y();

	SDL_RenderCopy(getRenderer(),texture,NULL, &rect);
}

inline void GraphicDevice::drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size, float angle)
{
	SDL_Rect rect;
	rect.x = (int)position.get_X();
	rect.y = (int)position.get_Y();
	rect.w = (int)size.get_X();
	rect.h = (int)size.get_Y();
	SDL_RenderCopyEx(getRenderer(),texture,NULL,&rect,angle,NULL,SDL_FLIP_NONE);
}

  
inline void GraphicDevice::drawText(const std::string text,const SDL_Color textColor,const  Vector2 position,const float size)
{
	if(getInstance().font)
	{
		SDL_Surface *textSurface;
		if(textSurface = TTF_RenderText_Solid(getInstance().font,text.c_str(),textColor))
		{
			SDL_Texture *textTexture = SDL_CreateTextureFromSurface(getRenderer() ,textSurface);
			Vector2 surfaceSize(textSurface->w * size/textSurface->h , size);
			SDL_FreeSurface(textSurface);
			if(textTexture ==NULL)throw GameError("Draw Text CreateTextureFromSurface failed: ", SDL_GetError());				
				drawTexture(textTexture,position,surfaceSize);			
				SDL_DestroyTexture(textTexture);			
		}else throw GameError("Text render error: ", TTF_GetError());		
	}else throw GameError("Font not Found");
}

inline const SDL_Color GraphicDevice::getColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	SDL_Color color= {r,g,b,a};
	return color;
}

#endif
