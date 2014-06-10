#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GraphicDevice.h"
#include "GameStateManager.h"
#include "Vector2.h"
#include "Sea.h"
#include "GameObject.h"
#include "Menu.h"
#include "FloatingObject.h"
#include "Ship.h"
#include "Textures.h"
#include "FishingRod.h"
#include "Barrel.h"
#include "InstantionManager.h"

int main( int argc, char* args[] )
{
SDL_Init(SDL_INIT_EVERYTHING);
IMG_Init(IMG_INIT_PNG);
GraphicDevice graphicDivice("Dzielny Pirat", Vector2(200,100),Vector2(1000,600));
Textures textures("ImagesName.txt", "images/");
Time time;

Ship ship(FloatingObject(Vector2(100,0), Vector2(150,150), 0, Textures::getTexture("ship.png"), Vector2(200,145), Vector2(150, 145)));
Sea sea(Vector2(0,300),Vector2(1005,42),0,Textures::getTexture("sea.png"), 0.15f);

GameStateManager gameStateManager(1);

SDL_Surface *bmpp = IMG_Load("images/start.png");
Menu menu(Textures::getTexture("background.bmp"));


InstantionManager<Barrel> barrelMenager("burrels.txt", Vector2(1100,300),0, Delay(1000), Delay(30000));
InstantionManager<Fish> fishesMenager("Fishes.txt", Vector2(1100,350),250, Delay(1000), Delay(30000));

while(gameStateManager.update())
{
	time.update();
	switch(gameStateManager.getGameState()){
	case 2:
		barrelMenager.update();
		fishesMenager.update();
		ship.update();
		sea.update();	
			
		graphicDivice.begin();
			SDL_RenderCopy(graphicDivice.getRenderer() , Textures::getTexture("background.bmp"),NULL, NULL);
			sea.draw();			
			ship.draw();
			barrelMenager.draw();
			fishesMenager.draw();
			
		graphicDivice.end();
		break;
	case 1:
		gameStateManager.setGameState(menu.update());
		graphicDivice.begin();		
			menu.draw();
		graphicDivice.end();
		break;
	default:
		exit(0);
		break;
	}
}

SDL_Quit();

return 0;
}