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

	try
	{
		loadIcon();
	}catch(GameError & error)
	{
		error.generateErrorLog(errorFile);	
	}

	initPointerObject();	
}

void GraphicDevice::loadIcon()
{
	SDL_Surface * icon = NULL;

	if((icon = SDL_LoadBMP((resourcesPath+ texturesPath+iconFile).c_str()))!=NULL)
	{
		SDL_SetWindowIcon(window, icon); 
		SDL_FreeSurface(icon);
	}else throw GameError("File not found :",resourcesPath+ texturesPath+iconFile);
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



GraphicDevice * GraphicDevice::instance = NULL;