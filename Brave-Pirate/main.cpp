#pragma once
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
#include "Player.h"


string intToStr(int n);

int main( int argc, char* args[] )
{
IMG_Init(IMG_INIT_PNG);
Time time;

Ship ship(FloatingObject(Vector2(100,0), Vector2(150,150), 0, "ship.png", Vector2(200,145), Vector2(150, 145)));
Sea sea(Vector2(0,300),Vector2(1005,42),0,"sea.png", 0.15f);

GameStateManager gameStateManager(1);

Menu menu(Textures::getTexture("background.bmp"));
InstantionManager<Barrel> barrelMenager("burrels.txt", Vector2(1100,300),0, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));
InstantionManager<Fish> fishesMenager("Fishes.txt", Vector2(1100,350),250, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));

Interface _interface(Vector2(0,0),Vector2(1000,100),NULL);

ProgressIndicator *shipHealth = new ProgressIndicator(Vector2(10,10),Vector2(200,20),"HP" ,GraphicDevice::getColor(240,0,0,255));
ProgressIndicator *pirateHealth = new ProgressIndicator(Vector2(10,35),Vector2(200,20), "Energy",GraphicDevice::getColor(0,240,0,255));
GameLabel *scor = new GameLabel("Score", GraphicDevice::getColor(0,0,0,255),Vector2(700,10),30);
GameLabel *scorValue = new GameLabel("", GraphicDevice::getColor(0,0,0,255),Vector2(800,10),30);

_interface.addObject(shipHealth);
_interface.addObject(pirateHealth);
_interface.addObject(scor);
_interface.addObject(scorValue);

while(gameStateManager.update())
{
	time.update();
	switch(gameStateManager.getGameState())
	{
	case 2:
		{
			barrelMenager.update();
			fishesMenager.update();		
		
			ship.update();
			sea.update();

			shipHealth->setPercentageValue(Player::getInstance().getShipHealth());
			pirateHealth->setPercentageValue(Player::getInstance().getPlayerEnergy());
			scorValue->setText(intToStr(Player::getInstance().getScor()));
			
			GraphicDevice::begin();
				SDL_RenderCopy(GraphicDevice::getRenderer() , Textures::getTexture("background.bmp"),NULL, NULL);
				ship.draw();
				sea.draw();	
				ship.lateDraw();
				barrelMenager.draw();
				fishesMenager.draw();

				_interface.draw();			
			GraphicDevice::end();
		}break;
	case 1:
		gameStateManager.setGameState(menu.update());
		GraphicDevice::begin();		
			menu.draw();
		GraphicDevice::end();
		break;
	}
}


Barrel::free();
Player::free();
Textures::free();
GraphicDevice::free();

SDL_Quit();
return 0;
}



string intToStr(int n)
{
     string tmp;
     if(n < 0) {
      tmp = "-";
      n = -n;
     }
     if(n > 9)
      tmp += intToStr(n / 10);
     tmp += n % 10 + 48;
     return tmp;
}