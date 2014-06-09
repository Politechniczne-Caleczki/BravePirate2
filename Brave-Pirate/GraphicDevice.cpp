#include "GraphicDevice.h"

//Constructors and destructors

GraphicDevice::GraphicDevice(string windowName, Vector2 windowPosition, Vector2 windowSize):
	windowName(windowName), 
	windowPosition(windowPosition), 
	windowSize(windowSize)
{
	setWindow();
	GraphicDevice::renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

SDL_Renderer* GraphicDevice::getRenderer()
{
	return renderer;
}

//Functions
void GraphicDevice::begin()
{
	SDL_RenderClear(renderer);
}

void GraphicDevice::end()
{
	SDL_RenderPresent(renderer);
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

SDL_Renderer* GraphicDevice::renderer = NULL;