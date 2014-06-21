#ifndef Textures_h
#define Textures_h
#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include "GraphicDevice.h"
#include "ConstantAndDefinitions.h"

typedef std::unordered_map<std::string, SDL_Texture*> TextureMap;

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

#endif