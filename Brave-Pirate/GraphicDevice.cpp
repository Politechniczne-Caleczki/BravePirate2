#include "GraphicDevice.h"

//Constructors and destructors

GraphicDevice::GraphicDevice():window(NULL), renderer(NULL), font(NULL)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	std::ifstream file(resourcesPath+windowSettings);
	if(file.is_open())
	{
		getline(file,windowName);
		file>>windowPosition>>windowSize;
	}
	else
	setWindow();

	window = SDL_CreateWindow(windowName.data(), (int)windowPosition.get_X(),
	(int)windowPosition.get_Y(), (int)windowSize.module().get_X(), (int)windowSize.module().get_Y(), SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	TTF_Init();
	font = TTF_OpenFont( (resourcesPath+fontName).c_str() ,128);//error
	if(font)
	{
		TTF_SetFontStyle(font,TTF_STYLE_BOLD);		
	}
}


void GraphicDevice::free()
{
	if(instance!=NULL)
	{
		delete instance;
		instance = NULL;
	}	
}

GraphicDevice::~GraphicDevice(void)
{	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
}

//Getters and Setters
void GraphicDevice::setWindow(void)
{
	windowName = DEFAULT_WIN_NAME;
	windowPosition = Vector2(DEFAULT_POS_X ,DEFAULT_POS_Y);
	windowSize = Vector2(DEFAULT_SIZE_W,DEFAULT_SIZE_H);
}

void GraphicDevice::setWindowName(const std::string name)
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

	SDL_RenderCopy(getRenderer(),texture,NULL, &rect);
}

void GraphicDevice::drawTexture(SDL_Texture *texture, const  Vector2 position,const Vector2 size, float angle)
{
	SDL_Rect rect;
	rect.x = (int)position.get_X();
	rect.y = (int)position.get_Y();
	rect.w = (int)size.get_X();
	rect.h = (int)size.get_Y();
	SDL_RenderCopyEx(getRenderer(),texture,NULL,&rect,angle,NULL,SDL_FLIP_NONE);
}


void GraphicDevice::drawText(const std::string text,const SDL_Color textColor,const  Vector2 position,const float size)
{
	if(getInstance().font)
	{
		SDL_Surface *textSurface;
		if(textSurface = TTF_RenderText_Solid(getInstance().font,text.c_str(),textColor))
		{
			SDL_Texture *textTexture = SDL_CreateTextureFromSurface(getRenderer() ,textSurface);
			Vector2 surfaceSize(textSurface->w * size/textSurface->h , size);
			drawTexture(textTexture,position,surfaceSize);			
			SDL_DestroyTexture(textTexture);
		}
		SDL_FreeSurface(textSurface);
	}
}

const SDL_Color GraphicDevice::getColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	SDL_Color color= {r,g,b,a};
	return color;
}

GraphicDevice * GraphicDevice::instance = new GraphicDevice();