#include "Player.h"


Player::Player(void): carHealth(100),playerEnergy(100), scor(0)
{
	atexit(free);
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

void Player::reset()
{
	this->carHealth = 100;
	this->playerEnergy = 100;
	this->scor = 0;
}

std::ostream & operator<< (std::ostream &w, const Player &p)
{
	return w<<p.carHealth<<" "<<p.playerEnergy<<" "<<p.scor<<" ";
}

std::istream & operator>> (std::istream &w, Player &p)
{
	w>>p.carHealth>>p.playerEnergy>>p.scor;
	return w;
}

Player * Player::instance = new Player();

