#pragma once
#include "GameStateManager.h"
#include "Desert.h"
#include "Menu.h"
#include "Car.h"
#include "ProgressIndicator.h"
#include "GameLabel.h"

int startGame(Container *c)
{
	if(c!=NULL)
	{
		if((c->obstacle == NULL) || (c->metal==NULL) || (c->desert==NULL) || (c->car==NULL) ||( c->time==NULL) || (Player::getInstance().getCarHealth() <=0))
		{		
			if (Player::getInstance().getCarHealth() <= 0)
				c->free();
			c->car    = new Car(FloatingObject(Vector2(100, 0), Vector2(150, 80), 0, "car.png", Vector2(190,110), Vector2(110, 110)), 0.1f, 0.4f,
				Magnet(Vector2(100, 0), Vector2(15,20), 0, "magnet.png", 0.08f), Gun(0,10, Vector2(150,0), Delay(400) , 3), "wheel.png", 40);
			Desert::level = 310;
			Desert::waveHeight = 21;
			c->desert     = new Desert(Vector2(0,0),Vector2(1005,342),0,"desert.png", 0.15f);
			c->time    = new Time();
			c->obstacle = new InstanceManager<Obstacle>("Obstacle.txt", Vector2(GraphicDevice::getWindowSize().get_X(), c->desert->getPosition().get_Y()),0, Delay(4500), Delay(25000));
			c->metal  = new InstanceManager<Metal>("Metal.txt",	  Vector2(GraphicDevice::getWindowSize().get_X() ,c->desert->getPosition().get_Y()+ c->desert->getSize().get_Y()),250, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));       
			Time::reset();

			Player::getInstance().reset();
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
		if(!((c->obstacle == NULL) || (c->metal==NULL) || (c->desert==NULL) || (c->car==NULL) ||( c->time==NULL) || (Player::getInstance().getCarHealth() <=0)))
		{
			std::ofstream file(resourcesPath+saveFile);
			if(file.is_open())
			{
				file<<*c->obstacle;
				file<<*c->metal;
				file<<*c->car;
				file<<*c->time;
				file<<*c->desert;
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
		file>>*c->obstacle;
		file>>*c->metal;
		file>>*c->car;
		file>>*c->time;
		file>>*c->desert;
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
		menu.addButton(Button(1, 1, Vector2(310, 100), Vector2(350, 57), Textures::getTexture("start.png"), Textures::getTexture("start_pressed.png"), startGame, &container));
		menu.addButton(Button(0, 1, Vector2(310, 170), Vector2(350, 57), Textures::getTexture("load.png"), Textures::getTexture("load_pressed.png"), loadGame, &container));
		menu.addButton(Button(0, 1, Vector2(310, 240), Vector2(350, 57), Textures::getTexture("save.png"), Textures::getTexture("save_pressed.png"), saveGame, &container));
		menu.addButton(Button(0, 1, Vector2(310, 310), Vector2(350, 57), Textures::getTexture("credits.png"), Textures::getTexture("credits_pressed.png"), credits, NULL));
		menu.addButton(Button(0, 1, Vector2(310, 380), Vector2(350, 57), Textures::getTexture("exit.png"), Textures::getTexture("exit_pressed.png"), leaveGame, &container));

		Interface _interface(Vector2(0, 0), Vector2(1000, 100), NULL);

		ProgressIndicator *carHealth = new ProgressIndicator(Vector2(10, 10), Vector2(200, 20), "HP", GraphicDevice::getColor(240, 0, 0, 255));
		ProgressIndicator *driverHealth = new ProgressIndicator(Vector2(10, 35), Vector2(200, 20), "Energy", GraphicDevice::getColor(0, 240, 0, 255));
		GameLabel *scor = new GameLabel("Score", GraphicDevice::getColor(0, 0, 0, 255), Vector2(700, 10), 30);
		GameLabel *time = new GameLabel("Time", GraphicDevice::getColor(0, 0, 0, 255), Vector2(700, 40), 30);

		_interface.addObject(carHealth);
		_interface.addObject(driverHealth);
		_interface.addObject(scor);
		_interface.addObject(time);


		Obstacle::loadBonus(resourcesPath + bonusFile);
		Vector2 gameOverPos((GraphicDevice::getWindowSize().get_X() - gameOverSize.get_X()) / 2, GraphicDevice::getWindowSize().get_Y());

		while (gameStateManager.update())
		{
			switch (gameStateManager.getGameState())
			{
			case 3:
			{
				GraphicDevice::begin();
				GraphicDevice::drawTexture(Textures::getTexture("background.bmp"), Vector2(0, 0), GraphicDevice::getWindowSize());
				GraphicDevice::drawTexture(Textures::getTexture("creditstext.png"), Vector2(30, 30), Vector2(484, 220));
				GraphicDevice::drawTexture(Textures::getTexture("grindgears.jpg"), Vector2(500, 220), Vector2(400, 300));
				GraphicDevice::drawTexture(Textures::getTexture("hammer.png"), Vector2(30, 500), Vector2(500, 60));
				GraphicDevice::end();
			}
			break;

			case 2:
			{
				if (Player::getInstance().getCarHealth() > 0)
				{
					container.update();

					carHealth->setPercentageValue(Player::getInstance().getCarHealth());
					driverHealth->setPercentageValue(Player::getInstance().getPlayerEnergy());
					scor->setText("Score: " + intToStr(Player::getInstance().getScor()));
					time->setText("Time: " + intToStr(Time::gameTime() / 1000));
				}
				else if (gameOverPos.get_Y() > ((GraphicDevice::getWindowSize().get_Y() - gameOverSize.get_Y()) / 2))
					gameOverPos.set_Y(gameOverPos.get_Y() - (Time::deltaTime()));

				GraphicDevice::begin();
				GraphicDevice::drawTexture(Textures::getTexture("background.bmp"), Vector2(0, 0), GraphicDevice::getWindowSize());

				container.draw();

				_interface.draw();
				if (Player::getInstance().getCarHealth() <= 0)
					GraphicDevice::drawTexture(Textures::getTexture("gameOver.png"), gameOverPos, Vector2(400, 400));
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
	}
	catch (GameError & error)
	{
		error.generateErrorLog("ErrorLog.txt");
		container.free();
	} 
	
	SDL_Quit();
	return 0;
}