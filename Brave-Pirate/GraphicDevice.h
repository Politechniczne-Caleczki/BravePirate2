#pragma once
#include <iostream>
#include "SDL.h"
#include "Vector2.h"

using namespace std;

class GraphicDevice
{
private:
	SDL_Window* window;
	static SDL_Renderer* renderer;
	string windowName; 
	Vector2 windowPosition, windowSize;
	void setWindow(void);

public:
	GraphicDevice(string windowName, Vector2 windowPosition, Vector2 windowSize);
	~GraphicDevice(void);

	void setWindowSize(const Vector2 size);
	void setWindowPosition(const Vector2 position);
	void setWindowName(const string name);
	static SDL_Renderer* getRenderer(void);//error

	static void drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size);
	static void drawTexture(SDL_Texture *texture,const Vector2 position,const Vector2 size, float angle);
	static void begin(void);
	static void end(void);
};

