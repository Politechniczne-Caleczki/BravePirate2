#pragma once
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include "GraphicDevice.h"
#include "ConstantAndDefinitions.h"
#include "string"

typedef unordered_map<string, SDL_Texture*> TextureMap;

class Textures
{
private:
	#define errorImage "errorImage"
	static TextureMap textures;
	static TextureMap initializeHashmap(); 
	static SDL_Texture * createErrorTexture();
	static SDL_Texture * findImage(const std::string);	
public:	
	static void free(void);
	static SDL_Texture* getTexture(std::string imageName);
};

