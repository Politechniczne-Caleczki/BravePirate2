#pragma once
#include "GameStateManager.h"
#include "Sea.h"
#include "Menu.h"
#include "Ship.h"
#include "ProgressIndicator.h"
#include "GameLabel.h"

int startGame(Container *c)
{
	if(c!=NULL)
	{
		if((c->barrels == NULL) || (c->fishes==NULL) || (c->sea==NULL) || (c->ship==NULL) ||( c->time==NULL) || (Player::getInstance().getShipHealth() <=0))
		{			
			Player::free();
			c->free();
			c->ship    = new Ship(FloatingObject(Vector2(100, 0), Vector2(150, 150), 0, "ship.png", Vector2(200,145), Vector2(150, 145)), 0.1f, 0.4f,
				FishingRod(Vector2(100, 0), Vector2(15,20), 0, "hook.png", 0.08f), Cannon(0,10, Vector2(100,0), Delay(400) , 3));
			Sea::seaLevel = 310;
			Sea::waveHeight = 21;
			c->sea     = new Sea(Vector2(0,0),Vector2(1005,342),0,"sea.png", 0.15f);
			c->time    = new Time();
			c->barrels = new InstantionManager<Barrel>("barrels.txt", Vector2(GraphicDevice::getWindowSize().get_X(), c->sea->getPosition().get_Y()),0, Delay(4500), Delay(25000));
			c->fishes  = new InstantionManager<Fish>("Fishes.txt",	  Vector2(GraphicDevice::getWindowSize().get_X() ,c->sea->getPosition().get_Y()+ c->sea->getSize().get_Y()),250, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));       
			Time::reset();
		}		
		Time::continueTime();
		return 2;
	}
	return 1;
} 

int leaveGame(Container *c)
{	
	if(c!=NULL)
		c->free();	
	return 0;
}

int saveGame(Container *c)
{
	if(c!=NULL)
	{
		if(!((c->barrels == NULL) || (c->fishes==NULL) || (c->sea==NULL) || (c->ship==NULL) ||( c->time==NULL) || (Player::getInstance().getShipHealth() <=0)))
		{
			std::ofstream file(resourcesPath+saveFile);
			if(file.is_open())
			{
				file<<*c->barrels;
				file<<*c->fishes;
				file<<*c->ship;
				file<<*c->time;
				file<<*c->sea;
				file<<Player::getInstance();
				file.close();
			}else throw GameError("Can not open file", resourcesPath+saveFile);		
		}
	}
	return 1;
}

int credits(Container *c)
{
	return 3;
}

int loadGame(Container *c)
{	
	startGame(c);
	std::ifstream file(resourcesPath+saveFile);
	if(file.is_open())
	{		
		file>>*c->barrels;
		file>>*c->fishes;
		file>>*c->ship;
		file>>*c->time;
		file>>*c->sea;
		file>>Player::getInstance();
		file.close();
		return 2;
	}	
	return 1;
}

std::string intToStr(int n)
{
	std::string tmp;
	if(n < 0) {
		tmp = "-";
		n = -n;
	}
	if(n > 9)
		tmp += intToStr(n / 10);
	tmp += n % 10 + 48;
	return tmp;
}

int main( int argc, char* args[] )
{
	Container container= {NULL,NULL,NULL,NULL,NULL};   
	try
	{
		Textures::initialize();
		
		GameStateManager gameStateManager(1);
		Menu menu(Textures::getTexture("menuBackground.png"));
		menu.addButton(Button(1,1,Vector2(310,100),Vector2(350,57), Textures::getTexture("start.png")    ,       Textures::getTexture("start_pressed.png")    ,  startGame, &container));
		menu.addButton(Button(0,1,Vector2(310,170),Vector2(350,57),Textures::getTexture("load.png")		 ,       Textures::getTexture("load_pressed.png")	  ,  loadGame,  &container));      
		menu.addButton(Button(0,1,Vector2(310,240),Vector2(350,57),Textures::getTexture("save.png")     ,       Textures::getTexture("save_pressed.png")     ,  saveGame,  &container));      
		menu.addButton(Button(0,1,Vector2(310,310),Vector2(350,57),Textures::getTexture("credits.png")  ,       Textures::getTexture("credits_pressed.png")  ,  credits, NULL));      
		menu.addButton(Button(0,1,Vector2(310,380),Vector2(350,57),Textures::getTexture("exit.png")     ,       Textures::getTexture("exit_pressed.png")     ,  leaveGame, &container));      

		Interface _interface(Vector2(0,0),Vector2(1000,100),NULL);

		ProgressIndicator *shipHealth = new ProgressIndicator(Vector2(10,10),Vector2(200,20),"HP" ,GraphicDevice::getColor(240,0,0,255));
		ProgressIndicator *pirateHealth = new ProgressIndicator(Vector2(10,35),Vector2(200,20), "Energy",GraphicDevice::getColor(0,240,0,255));
		GameLabel *scor = new GameLabel("Score", GraphicDevice::getColor(0,0,0,255),Vector2(700,10),30);
		GameLabel *time = new GameLabel("Time", GraphicDevice::getColor(0,0,0,255),Vector2(700,40),30);

		_interface.addObject(shipHealth);
		_interface.addObject(pirateHealth);
		_interface.addObject(scor);
		_interface.addObject(time);


		Barrel::loadBonus(resourcesPath+bonusFile);
		Vector2 gameOverPos((GraphicDevice::getWindowSize().get_X()-gameOverSize.get_X())/2, GraphicDevice::getWindowSize().get_Y());
		while(gameStateManager.update())
		{               
			switch(gameStateManager.getGameState())
			{
			case 3:
				{
					GraphicDevice::begin();
					GraphicDevice::drawTexture(Textures::getTexture("background.bmp"),Vector2(0,0),GraphicDevice::getWindowSize());
					GraphicDevice::drawTexture(Textures::getTexture("creditstext.png"),Vector2(30,30),Vector2(484,220));
					GraphicDevice::drawTexture(Textures::getTexture("grindgears.jpg"),Vector2(500,220),Vector2(400,300));
					GraphicDevice::drawTexture(Textures::getTexture("hammer.png"),Vector2(30,500),Vector2(500,60));
					GraphicDevice::end();
				}
				break;

			case 2:
				{        
					if(Player::getInstance().getShipHealth()>0)
					{
						container.time->update();
						container.barrels->update();
						container.fishes->update();                             
						container.ship->update();
						container.sea->update();

						shipHealth->setPercentageValue(Player::getInstance().getShipHealth());
						pirateHealth->setPercentageValue(Player::getInstance().getPlayerEnergy());
						scor->setText("Score: "+intToStr(Player::getInstance().getScor()));     
						time->setText("Time: "+intToStr(Time::gameTime()/1000));  
					}else if(gameOverPos.get_Y()> ((GraphicDevice::getWindowSize().get_Y()-gameOverSize.get_Y())/2))
						gameOverPos.set_Y(gameOverPos.get_Y() - (Time::deltaTime()));

					GraphicDevice::begin();
					GraphicDevice::drawTexture(Textures::getTexture("background.bmp"),Vector2(0,0),GraphicDevice::getWindowSize());
					container.ship->draw();
					container.barrels->draw();											
					container.sea->draw();  
					container.fishes->draw();
					container.ship->lateDraw();
					_interface.draw();   
					if(Player::getInstance().getShipHealth()<=0)
						GraphicDevice::drawTexture(Textures::getTexture("gameOver.png"),gameOverPos,Vector2(400,400));
					GraphicDevice::end();
				}break;
			case 1:
				{
					gameOverPos.set_Y(GraphicDevice::getWindowSize().get_Y());
					gameStateManager.setGameState(menu.update());
					GraphicDevice::begin();         
						menu.draw();
					GraphicDevice::end();
				}break;
			}
		}

	}catch(GameError & error)
	{
		error.generateErrorLog("ErrorLog.txt");
		container.free();
	} 

	Barrel::free();
	Player::free();
	Textures::free();
	GraphicDevice::free();

	SDL_Quit();
	return 0;
}