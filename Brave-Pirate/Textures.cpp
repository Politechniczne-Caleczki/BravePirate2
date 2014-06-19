#include "Textures.h"

//Constructors and destructors
Textures::Textures(string filename, string path)
{
	SDL_Surface *surface =NULL;	
	SDL_Texture *texture = NULL;
	if((surface = IMG_Load("Resources/images/error.png"))!=NULL)//error
	{
		if((texture = SDL_CreateTextureFromSurface(GraphicDevice::getRenderer(),surface))!=NULL)//error
		{
			textures.insert(TextureMap::value_type("error.png",texture));

			ifstream myfile (path+filename);
			if (myfile.is_open())//error
			{				
				string imageName;
				while ( getline (myfile,imageName) )
				{					
					if( (surface = IMG_Load((path+imageName).data()))!=NULL)//error
					{
						if((texture = SDL_CreateTextureFromSurface(GraphicDevice::getRenderer(),surface))!=NULL)
						{
							textures.insert(TextureMap::value_type(imageName,texture));					
						}
					}
					surface =NULL;
					texture = NULL;
				}
				myfile.close();
			}
		}
	}
	SDL_FreeSurface(surface);
}

Textures::~Textures(void)
{
	for(TextureMap::iterator it = Textures::textures.begin(); it!=textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	textures.clear();
}

//Functions
SDL_Texture* Textures::getTexture(string imageName)
{
	TextureMap::iterator it = Textures::textures.find(imageName);

	if(it!=textures.end())
	{
		return it->second;
	}else
	{
		return textures["error.png"];
	}
}

TextureMap Textures::getErrorImage()
{
	TextureMap _tm;
	return _tm;
}

TextureMap Textures::textures = Textures::getErrorImage();
