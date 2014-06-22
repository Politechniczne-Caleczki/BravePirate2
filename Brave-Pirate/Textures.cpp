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
SDL_Texture* Textures::getTexture(std::string imageName)
{
	TextureMap::iterator it = Textures::textures.find(imageName);

	if(it!=textures.end())
	{
		return it->second;
	}else
	{
		try
		{
			return findImage(imageName);
		}
		catch(GameError & error)
		{
			error.generateErrorLog(errorFile);
			textures.insert(TextureMap::value_type(imageName,textures[errorImage]));
			return textures[errorImage];
		}
	}
}

SDL_Texture * Textures::findImage(std::string imageName)
{
	SDL_Surface *surface =NULL;	
	if((surface = IMG_Load(( resourcesPath+texturesPath+imageName).c_str()))!=NULL)
	{
		SDL_Texture *texture = NULL;
		if((texture = SDL_CreateTextureFromSurface(GraphicDevice::getRenderer(),surface))!=NULL)
		{
			textures.insert(TextureMap::value_type(imageName,texture));
			SDL_FreeSurface(surface);
			return texture;
		}throw GameError("CreateTextureFromSurface failed: "+ imageName+ " ", SDL_GetError());
	}throw GameError("Texture not found: ", imageName);

	SDL_FreeSurface(surface);	
}

SDL_Texture* Textures::createErrorTexture()
{
	SDL_Surface *surf = SDL_CreateRGBSurface(0,3,3,32,0,0,0,0);
	if(surf == NULL)throw GameError("CreateRGBSurface: ", SDL_GetError());
	uint32_t *pixels = (uint32_t*)surf->pixels;

	for(unsigned i = 0; i <9;i+=2)
	{
		pixels[i] = SDL_MapRGB(surf->format,255, 0, 0);		
		pixels[i+1] = SDL_MapRGB(surf->format,0, 255, 0);		
	}
	SDL_Texture *text = SDL_CreateTextureFromSurface(GraphicDevice::getInstance().getRenderer(),surf);
	SDL_FreeSurface(surf);
	if(text ==NULL)throw GameError("CreateTextureFromSurface failed: ", SDL_GetError());
	
	return text;
}

void Textures::initialize()
{
	try
	{
		textures.insert(TextureMap::value_type(errorImage,createErrorTexture()));
	}catch(GameError & error)
	{
		error.generateErrorLog(errorFile);
		throw;
	}

	try
	{
		loadIcon();
	}catch(GameError & error)
	{
		error.generateErrorLog(errorFile);	
	}
}

void Textures::loadIcon()
{
	SDL_Surface * icon = NULL;

	if((icon = IMG_Load((resourcesPath+ texturesPath+iconFile).c_str()))!=NULL)
	{
		SDL_SetWindowIcon(GraphicDevice::getWindow() , icon); 
		SDL_FreeSurface(icon);
	}else throw GameError("File not found :",resourcesPath+ texturesPath+iconFile);
}

TextureMap Textures::initializeHashmap()
{
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if(initted&flags != flags)throw GameError("Failed to init required jpg or png support: ", SDL_GetError());

	TextureMap _tm;
	return _tm;
}

TextureMap Textures::textures = Textures::initializeHashmap();
