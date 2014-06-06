#include "Menu.h"
//Buttons functions
int startGame(){
	return 2;
}
int leaveGame(){
	return 0;
}
//Constructors and destructors
Menu::Menu():selected(0),keyPressed(false)
{	
	background = Textures::getTexture("bacground.bmp");
	buttonList = new Button*[5];
	buttonList[0]=new Button(1,1,Vector2(340,30), Textures::getTexture("start.png"),	Textures::getTexture("start_pressed.png"),startGame);
	buttonList[1]=new Button(0,1,Vector2(340,140),Textures::getTexture("load_game.png"),	Textures::getTexture("load_game_pressed.png"),startGame);	
	buttonList[2]=new Button(0,1,Vector2(340,250),Textures::getTexture("save.png"),	Textures::getTexture("save_pressed.png"),startGame);	
	buttonList[3]=new Button(0,1,Vector2(340,360),Textures::getTexture("credits.png"),	Textures::getTexture("credits_pressed.png"),startGame);	
	buttonList[4]=new Button(0,1,Vector2(340,470),Textures::getTexture("exit.png"),	Textures::getTexture("exit_pressed.png"),leaveGame);		
}

Menu::Menu(SDL_Texture * background):background(background),selected(0),keyPressed(false)
{
	buttonList = new Button*[5];
	buttonList[0]=new Button(1,1,Vector2(340,30), Textures::getTexture("start.png"),	Textures::getTexture("start_pressed.png"),startGame);
	buttonList[1]=new Button(0,1,Vector2(340,140),Textures::getTexture("load_game.png"),	Textures::getTexture("load_game_pressed.png"),startGame);	
	buttonList[2]=new Button(0,1,Vector2(340,250),Textures::getTexture("save.png"),	Textures::getTexture("save_pressed.png"),startGame);	
	buttonList[3]=new Button(0,1,Vector2(340,360),Textures::getTexture("credits.png"),	Textures::getTexture("credits_pressed.png"),startGame);	
	buttonList[4]=new Button(0,1,Vector2(340,470),Textures::getTexture("exit.png"),	Textures::getTexture("exit_pressed.png"),leaveGame);		
}

Menu::~Menu()
{
	for(int i=0;i<5;i++)
		buttonList[0]->~Button();
}

//Functions
void Menu::draw(void)const{
	SDL_RenderCopy(GraphicDevice::getRenderer() , background,NULL, NULL);
	for(int i=0;i<5;i++){
		buttonList[i]->draw();
	}
}

int Menu::update()
{
	if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
	{
		if(keyPressed == false && selected<4){
			keyPressed=true;
			buttonList[selected]->setActive(0);
			++selected;
			buttonList[selected]->setActive(1);
		}
	}
	else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
	{
		if(keyPressed == false && selected>0){
			keyPressed=true;
			buttonList[selected]->setActive(0);
			--selected;
			buttonList[selected]->setActive(1);
		}
	}
	else if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RETURN])
	{
		return buttonList[selected]->action();	
	}
	else
		keyPressed =false;
	return 1;
}


