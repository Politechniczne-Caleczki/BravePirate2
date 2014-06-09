#pragma once
#include <list>
#include <cstddef>
#include <math.h>
#include "Vector2.h"
#include "SDL.h"
#include "GraphicDevice.h"
#include "BasicObject.h"

class GameObject;

typedef list<GameObject*> Lista;

class GameObject
{
private:
	static Lista getNewList();
protected:
	Vector2 position, size;
	float angle;
	SDL_Texture * texture;
	bool _isDestroyed; 
	void onDestroy(void);	
	bool onCollision(GameObject &gameObject)const;
public:
	static Lista fishesArrayPointer;
	static Lista barrelsArrayPointer;

	GameObject(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture);
	virtual~GameObject(void);

	Vector2 getPosition(void)const;
	Vector2 getCenterPosition(void)const;
	Vector2 getSize(void)const;
	SDL_Texture* getTexture(void)const;
	float getAngle(void)const;
	void setAngle(const float angle);
	void setPosition(const Vector2 position);
	void setsize(const Vector2 size);
	void setTexture(SDL_Texture* texture);	

	void draw()const;
	void update();	

	void onCollision(void);	
	void onCollision(const float strength);	
	bool isDestroyed()const;

	void operator=(GameObject &GameObject);
};



/*

class GameState,....

private: 
	int gameState;

0// exit game;
1// menu update
2// game update


int GameStateMEnager::Update()
{
	if( czy nacisniety klawisz X)
		set 0;


	if(gameState==2)
	{
		if(ESC);
			return 1;
		return 2;
	}	
}



GameStateMEnager gs(1);
while(gs.getState())
{
	swich(gs.Update())
	{
		case 1:
		{
			gs.setState(menu.Update());
			menu.Draw();
		}break;
		case 2:
		{
			//
			//
			//
			//
			//
			game.Update();
			game.Draw();
		}
	}
}

*/