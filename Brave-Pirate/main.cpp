#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
#include "Interface.h"
#include "ProgressIndicator.h"
#include "GameLabel.h"



int main( int argc, char* args[] )
{
SDL_Init(SDL_INIT_EVERYTHING);
IMG_Init(IMG_INIT_PNG);
TTF_Init();


GraphicDevice graphicDivice("Dzielny Pirat", Vector2(200,100),Vector2(1000,600));
Textures textures("ImagesName.txt", "images/");
Time time;

Ship ship(FloatingObject(Vector2(100,0), Vector2(150,150), 0, Textures::getTexture("ship.png"), Vector2(200,145), Vector2(150, 145)), 200,200,0);
Sea sea(Vector2(0,300),Vector2(1005,42),0,Textures::getTexture("sea.png"), 0.15f);

GameStateManager gameStateManager(1);

SDL_Surface *bmpp = IMG_Load("images/start.png");
Menu menu(Textures::getTexture("background.bmp"));


InstantionManager<Barrel> barrelMenager("burrels.txt", Vector2(1100,300),0, Delay(5000), Delay(100000));
InstantionManager<Fish> fishesMenager("Fishes.txt", Vector2(1100,350),250, Delay(5000), Delay(100000));

Interface _interface(Vector2(0,0),Vector2(1000,100),NULL);

ProgressIndicator *shipHealth = new ProgressIndicator(Vector2(10,10),Vector2(ship.getShipHealth(),20),"HP" ,graphicDivice.getColor(240,0,0,255));
ProgressIndicator *pirateHealth = new ProgressIndicator(Vector2(10,35),Vector2(ship.getPirateHealth(),20), "Energy",graphicDivice.getColor(0,240,0,255));
GameLabel *scor = new GameLabel("Napis", graphicDivice.getColor(0,0,0,255),Vector2(700,10),30);

_interface.addObject(shipHealth);
_interface.addObject(pirateHealth);
_interface.addObject(scor);


while(gameStateManager.update())
{
	time.update();
	switch(gameStateManager.getGameState()){
	case 2:
		barrelMenager.update();
		fishesMenager.update();
		ship.update();
		sea.update();	

		shipHealth->setValue(ship.getShipHealth());
		pirateHealth->setValue(ship.getPirateHealth());	
			
		graphicDivice.begin();

			SDL_RenderCopy(graphicDivice.getRenderer() , Textures::getTexture("background.bmp"),NULL, NULL);
			sea.draw();			
			ship.draw();
			barrelMenager.draw();
			fishesMenager.draw();

			_interface.draw();			
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