#include "Player.h"


Player::Player(void): shipHealth(100),playerEnergy(100), scor(0)
{

}

Player::~Player(void)
{
}

void Player::free()
{
	if(instance!=NULL)
	{
		delete instance;
		instance=NULL;
	}
}

Player * Player::instance = new Player();
