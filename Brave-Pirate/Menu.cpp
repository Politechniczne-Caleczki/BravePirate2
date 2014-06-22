#include "Menu.h"

//Constructors and destructors

Menu::Menu(SDL_Texture * background):background(background),buttonIterator(buttonList.begin()),keyPressed(false){}

Menu::~Menu()
{
	buttonList.clear();
}

//Functions
void Menu::draw(void)const
{
	SDL_RenderCopy(GraphicDevice::getRenderer() , background,NULL, NULL);
	for(ButtonList::const_iterator iter = buttonList.begin(); iter!=buttonList.end();iter++)
		(*iter).draw();
}

int Menu::update()
{
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
	{
		if(keyPressed == false)
		{
			keyPressed=true;
			(*buttonIterator).setActive(0);
			buttonIterator++;
			if( buttonIterator != buttonList.end())				
				(*buttonIterator).setActive(1);
			else
			{
				buttonIterator--;
				(*buttonIterator).setActive(1);
			}
		}
	}
	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
	{
		if(keyPressed == false && buttonIterator != buttonList.begin())
		{
			keyPressed=true;
			(*buttonIterator).setActive(0);
			buttonIterator--;
			(*buttonIterator).setActive(1);
		}
	}
	else if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
	{
		if(keyPressed == false)
		{
			keyPressed=true;
			if(buttonIterator!=buttonList.end())
			return (*buttonIterator).action();
		}
	}
	else
		keyPressed =false;
	return 1;
}

void Menu::addButton(const Button & button)
{
	buttonList.push_back(button);
	buttonIterator = buttonList.begin();
}


