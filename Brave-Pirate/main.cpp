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
                if((c->barrels == NULL) || (c->fishes==NULL) || (c->sea==NULL) || (c->ship==NULL) ||( c->time=NULL))
                {
                        c->free();
                        c->ship = new Ship(FloatingObject(Vector2(100,0), Vector2(150,150), 0, "ship.png", Vector2(200,145), Vector2(150, 145)));
                        c->sea = new Sea(Vector2(0,300),Vector2(1005,42),0,"sea.png", 0.15f);
                        c->time = new Time;
                        c->barrels = new InstantionManager<Barrel>("barrels.txt", Vector2(1100,300),0, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));
                        c->fishes = new InstantionManager<Fish>("Fishes.txt", Vector2(1100,350),250, Delay(INSTANTIATE_TIME), Delay(TIME_TO_NEXT_LEVEL));                       
                        return 2;
                }
        }
        return 1;
}
int leaveGame(Container *c)
{
        if(c!=NULL)
                c->free();
        return 0;
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
        GameStateManager gameStateManager(1);
        Menu menu(Textures::getTexture("background.bmp"));
        menu.addButton(Button(1,1,Vector2(340,30), Textures::getTexture("start.png")    ,       Textures::getTexture("start_pressed.png")    ,  startGame, &container));
        menu.addButton(Button(0,1,Vector2(340,140),Textures::getTexture("load_game.png"),       Textures::getTexture("load_game_pressed.png"),  startGame, NULL));      
        menu.addButton(Button(0,1,Vector2(340,250),Textures::getTexture("save.png")     ,       Textures::getTexture("save_pressed.png")     ,  startGame, NULL));      
        menu.addButton(Button(0,1,Vector2(340,360),Textures::getTexture("credits.png")  ,       Textures::getTexture("credits_pressed.png")  ,  startGame, NULL));      
        menu.addButton(Button(0,1,Vector2(340,470),Textures::getTexture("exit.png")     ,       Textures::getTexture("exit_pressed.png")     ,  leaveGame, NULL));      
 
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
                switch(gameStateManager.getGameState())
                {
                case 2:
                        {                               
                                container.time->update();
                                container.barrels->update();
                                container.fishes->update();                             
                                container.ship->update();
                                container.sea->update();
 
                                shipHealth->setPercentageValue(Player::getInstance().getShipHealth());
                                pirateHealth->setPercentageValue(Player::getInstance().getPlayerEnergy());
                                scorValue->setText(intToStr(Player::getInstance().getScor()));                  
                                GraphicDevice::begin();
                                        SDL_RenderCopy(GraphicDevice::getRenderer() , Textures::getTexture("background.bmp"),NULL, NULL);
                                        container.ship->draw();
                                        container.barrels->draw();
                                        container.fishes->draw();
                                        container.sea->draw();  
                                        container.ship->lateDraw();
                                        _interface.draw();                      
                                GraphicDevice::end();
                        }break;
                case 1:
                        {
                        gameStateManager.setGameState(menu.update());
                        GraphicDevice::begin();         
                                menu.draw();
                        GraphicDevice::end();
                        }break;
                }
        }
 
        Barrel::free();
        Player::free();
        Textures::free();
        GraphicDevice::free();
 
SDL_Quit();
return 0;
}