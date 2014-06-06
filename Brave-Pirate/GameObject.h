#pragma once
#include <list>
#include <cstddef>
#include <math.h>
#include "Vector2.h"
#include "SDL.h"
#include "GraphicDevice.h"

class GameObject;

typedef list<GameObject*> Lista;

class GameObject
{
private:
	static Lista getNewList();
protected:
	Vector2 position, scale;
	float angle;
	SDL_Texture * texture;
	bool _isDestroyed; 
	
public:
	static Lista fishesArrayPointer;
	static Lista barrelsArrayPointer;

	GameObject(void);
	GameObject(const Vector2 position, const Vector2 scale, const float angle, SDL_Texture* texture);
	virtual~GameObject(void);

	Vector2 getPosition(void)const;
	Vector2 getCenterPosition(void)const;
	Vector2 getScale(void)const;
	SDL_Texture* getTexture(void)const;
	float getAngle(void)const;
	void setAngle(const float angle);
	void setPosition(const Vector2 position);
	void setScale(const Vector2 scale);
	void setTexture(SDL_Texture* texture);
	
	virtual void draw(void)const;
	virtual void update(void);
	virtual void onCollision(void);
	virtual void onCollision(const float strength);
	virtual void onDestroy(void);
	bool isDestroyed()const;

	bool onCollision(GameObject &gameObject)const;

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