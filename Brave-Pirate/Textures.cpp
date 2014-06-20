#include "Textures.h"

//Constructors and destructors

void Textures::free()
{
	for(TextureMap::iterator it = Textures::textures.begin(); it!=textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	textures.clear();
}

//Functions
SDL_Texture* Textures::getTexture(string imageimageName)
{
	TextureMap::iterator it = Textures::textures.find(imageimageName);

	if(it!=textures.end())
	{
		return it->second;
	}else
	{
		return findImage(imageimageName);
	}
}

SDL_Texture * Textures::findImage(std::string imageName)
{
	SDL_Surface *surface =NULL;	
	if((surface = IMG_Load(( resourcesPath+texturesPath+imageName).c_str()))!=NULL)
	{
		SDL_Texture *texture = NULL;
		if((texture = SDL_CreateTextureFromSurface(GraphicDevice::getRenderer(),surface))!=NULL)//error
		{
			textures.insert(TextureMap::value_type(imageName,texture));
			SDL_FreeSurface(surface);
			return texture;
		}
	}
	SDL_FreeSurface(surface);
	return textures[errorImage];
}

SDL_Texture* Textures::createErrorTexture()
{
	SDL_Surface *surf = SDL_CreateRGBSurface(0,3,3,32,0,0,0,0);
	uint32_t *pixels = (uint32_t*)surf->pixels;

	for(unsigned i = 0; i <9;i+=2)
	{
		pixels[i] = SDL_MapRGB(surf->format,255, 0, 0);		
		pixels[i+1] = SDL_MapRGB(surf->format,0, 255, 0);		
	}
	SDL_Texture *text = SDL_CreateTextureFromSurface(GraphicDevice::getInstance().getRenderer(),surf);
	SDL_FreeSurface(surf);
	return text;
}

TextureMap Textures::initializeHashmap()
{
	TextureMap _tm;
	_tm.insert(TextureMap::value_type(errorImage,createErrorTexture()));
	return _tm;
}

TextureMap Textures::textures = Textures::initializeHashmap();
