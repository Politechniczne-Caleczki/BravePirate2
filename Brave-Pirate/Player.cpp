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

std::ostream & operator<< (std::ostream &w, const Player &p)
{
	return w<<p.shipHealth<<" "<<p.playerEnergy<<" "<<p.scor;
}

std::istream & operator>> (std::istream &w, Player &p)
{
	w>>p.shipHealth>>p.playerEnergy>>p.scor;
	return w;
}

Player * Player::instance = new Player();

