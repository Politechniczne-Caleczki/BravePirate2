#pragma once
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include "GraphicDevice.h"

using namespace std;
typedef unordered_map<string, SDL_Texture*> TextureMap;

class Textures
{
	static TextureMap textures, getErrorImage();

public:
	Textures(string filename, string path);
	~Textures(void);

	static SDL_Texture* getTexture(string imageName);
};

