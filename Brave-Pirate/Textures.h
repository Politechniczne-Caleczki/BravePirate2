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
	static void loadIcon();
	static void free(void);
public:	
	static SDL_Texture* getTexture(std::string imageName);
	static void initialize();
};

#endif