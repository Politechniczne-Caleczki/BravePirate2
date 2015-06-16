#ifndef Obstacle_h
#define Obstacle_h
#pragma once
#include "FloatingObject.h"
#include "Bonus.h"

class Obstacle : public FloatingObject
{
	typedef std::list<SampleBonus> SampleBonusList;
private:
	float health, damage;
	unsigned int scor;
	static SampleBonusList bonusList, initializeBonusList();
	void createBonus();		
	static void free();
public:
	Obstacle(const FloatingObject & , const float , const float , const unsigned int );
	~Obstacle(void);

	void update(void);
	void onCollision(void);
	void onCollision(const float strength);
	const float getDamage()const;
	const bool isDestroed()const;
	const unsigned int getScor()const;

	friend std::ostream & operator<< (std::ostream &, const Obstacle &);
	friend std::istream & operator>> (std::istream &, Obstacle &);	
	static void loadBonus(const std::string );
};

inline void Obstacle::onCollision(void)
{
	_isDestroyed= true;
}

inline const float Obstacle::getDamage()const
{	
	return this->damage;
}


inline const unsigned int Obstacle::getScor()const
{
	return this->scor;
}

#endif