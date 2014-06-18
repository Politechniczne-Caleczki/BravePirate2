#include "GraphicDevice.h"

//Constructors and destructors

GraphicDevice::GraphicDevice(string windowName, Vector2 windowPosition, Vector2 windowSize):
	windowName(windowName), 
	windowPosition(windowPosition), 
	windowSize(windowSize)
{
	setWindow();
	GraphicDevice::renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	font = TTF_OpenFont("arial.ttf",128);//error
	if(font)
		TTF_SetFontStyle(font,TTF_STYLE_BOLD);
}

GraphicDevice::~GraphicDevice(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

//Getters and Setters
void GraphicDevice::setWindow(void)
{
	window = SDL_CreateWindow(windowName.data(), (int)windowPosition.get_X(),
	(int)windowPosition.get_Y(), (int)windowSize.module().get_X(), (int)windowSize.module().get_Y(), SDL_WINDOW_SHOWN);
}

void GraphicDevice::setWindowName(const string name)
{
	windowName = name;
	setWindow();
}

void GraphicDevice::setWindowSize(const Vector2 size)
{
	windowSize = size.module();
	setWindow();
}

void GraphicDevice::setWindowPosition(const Vector2 position)
{
	windowPosition = position;
	setWindow();
}

void GraphicDevice::drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size)
{
	SDL_Rect rect;
	rect.x = (int)position.get_X();
	rect.y = (int)position.get_Y();
	rect.w = (int)size.get_X();
	rect.h = (int)size.get_Y();

	SDL_RenderCopy(renderer,texture,NULL, &rect);
}

void GraphicDevice::drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size, float angle)
{
	SDL_Rect rect;
	rect.x = (int)position.get_X();
	rect.y = (int)position.get_Y();
	rect.w = (int)size.get_X();
	rect.h = (int)size.get_Y();
	SDL_RenderCopyEx(renderer,texture,NULL,&rect,angle,NULL,SDL_FLIP_NONE);
}


void GraphicDevice::drawText(const string text,const SDL_Color textColor,const  Vector2 position,const float size)
{
	SDL_Surface *textSurface;
	if(textSurface = TTF_RenderText_Solid(font,text.c_str(),textColor))
	{
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer ,textSurface);
		Vector2 surfaceSize(textSurface->w * size/textSurface->h , size);
		drawTexture(textTexture,position,surfaceSize);			
		SDL_DestroyTexture(textTexture);
	}
	SDL_FreeSurface(textSurface);
}

const SDL_Color GraphicDevice::getColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	SDL_Color color= {r,g,b,a};
	return color;
}

SDL_Renderer* GraphicDevice::renderer = NULL;
TTF_Font * GraphicDevice::font = NULL;