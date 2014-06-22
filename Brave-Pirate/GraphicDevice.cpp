#include "GraphicDevice.h"

//Constructors and destructors

GraphicDevice::GraphicDevice():window(NULL), renderer(NULL), font(NULL)
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS)<0)throw GameError("SDL_Init failed: ", SDL_GetError());

	try
	{
		loadWindowsSetting();
	}catch(GameError & error)
	{
		error.generateErrorLog(errorFile);
		setWindow();
	}		
	initPointerObject();	
}

void GraphicDevice::loadWindowsSetting()
{
	std::ifstream file(resourcesPath+windowSettings);
	if(file.is_open())
	{
		getline(file,windowName);
		file>>windowPosition>>windowSize;
		file.close();
	}
	else throw GameError("File not found :",resourcesPath+windowSettings );
}

void GraphicDevice::initPointerObject()
{
		window = SDL_CreateWindow(windowName.data(), (int)windowPosition.get_X(),
	(int)windowPosition.get_Y(), (int)windowSize.module().get_X(), (int)windowSize.module().get_Y(), SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		deletePointerObject();
		throw GameError("Could not create window: ", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer==NULL)
	{	
		deletePointerObject();
		throw GameError("Could not create renderer: ", SDL_GetError());
	}

	if(TTF_Init()==-1)
	{
		deletePointerObject();	
		throw GameError("Unable to initialize TTF: ", TTF_GetError());
	}
	font = TTF_OpenFont( (resourcesPath+fontName).c_str() ,128);//error
	if(font)
	{
		TTF_SetFontStyle(font,TTF_STYLE_BOLD);		
	}else
	{
		deletePointerObject();
		throw GameError("Could not open font :"+resourcesPath+fontName);
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

void GraphicDevice::deletePointerObject()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
}

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
			if(textTexture ==NULL)throw GameError("CreateTextureFromSurface failed: ", SDL_GetError());
			else
			{
				Vector2 surfaceSize(textSurface->w * size/textSurface->h , size);
				drawTexture(textTexture,position,surfaceSize);			
				SDL_DestroyTexture(textTexture);
			}
		}else throw GameError("Text render error: ", TTF_GetError());		
	}else throw GameError("Font not Found");
}

const SDL_Color GraphicDevice::getColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	SDL_Color color= {r,g,b,a};
	return color;
}

GraphicDevice * GraphicDevice::instance = NULL;