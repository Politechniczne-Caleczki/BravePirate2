#ifndef Player_h
#define Player_h
#pragma once
#include <iostream>
class Player
{
private:
	float carHealth, playerEnergy;
	unsigned int scor;
	static Player *instance;
	Player(void);
	~Player(void);
	const float normalize(const float)const;
	static void free();
public:
	void setCarHealth(const float);	
	void setPlayerEnergy(const float);
	void setScor(const unsigned int);
	void addScor(const unsigned int);
	void addCarHealth(const float);
	void addPlayerEnery(const float);
	void removeScor(const unsigned int);
	void removeCarHealth(const float);
	void removePlayerEnery(const float);
	void reset();

	const float getCarHealth  ()const;
	const float getPlayerEnergy()const;
	const unsigned int	getScor()const;
	static Player & getInstance();
	

	friend std::ostream & operator<< (std::ostream &, const Player &);
	friend std::istream & operator>> (std::istream &, Player &);
};

inline const float Player::normalize(const float value)const
{
	if(value>100) return 100;
	if(value<0)	  return 0;
	
	return value;
}

inline void Player::setCarHealth(const float carHealth)
{
	this->carHealth = normalize(carHealth);
}

inline void Player::setPlayerEnergy(const float playerEnery)
{
	this->playerEnergy = normalize(playerEnery);
}

inline void Player::setScor(const unsigned int scor)
{
	this->scor = scor;
}

inline void Player::addScor(const unsigned int scor)
{
	this->scor+=scor;
}

inline void Player::addCarHealth(const float carHealth)
{
	setCarHealth(this->carHealth+carHealth);
}

inline void Player::addPlayerEnery(const float playerEnergy)
{
	setPlayerEnergy(this->playerEnergy + playerEnergy);
}

inline void Player::removeScor(const unsigned int scor)
{
	this->scor-=scor;
}

inline void Player::removeCarHealth(const float carHealth)
{
	setCarHealth(this->carHealth - carHealth);
}

inline void Player::removePlayerEnery(const float playerEnergy)
{
	setPlayerEnergy(this->playerEnergy - playerEnergy);
}

inline const unsigned int Player::getScor()const
{
	return scor;
}

inline const float Player::getPlayerEnergy()const
{
	return playerEnergy;
}

inline const float Player::getCarHealth()const
{
	return carHealth;
}

inline Player & Player::getInstance()
{
	if(instance==NULL)
		instance = new Player();

	return *instance;	
}

#endif