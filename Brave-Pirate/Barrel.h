#ifndef Barrel_h
#define Barrel_h
#pragma once
#include "FloatingObject.h"
#include "Bonus.h"

class Barrel : public FloatingObject
{
	typedef std::list<SampleBonus> SampleBonusList;
private:
	float health, speed, damage;
	unsigned int scor;
	static SampleBonusList bonusList, initializeBonusList();
	void createBonus();	
public:
	Barrel(const FloatingObject & , const float , const float , const float , const unsigned int );
	~Barrel(void);

	void update(void);
	void onCollision(void);
	void onCollision(const float strength);
	const float getDamage()const;
	const bool isDestroed()const;
	const unsigned int getScor()const;

	friend std::ostream & operator<< (std::ostream &, const Barrel &);
	friend std::istream & operator>> (std::istream &, Barrel &);
	static void free();
};

inline void Barrel::onCollision(void)
{
	_isDestroyed= true;
}

inline const float Barrel::getDamage()const
{	
	return this->damage;
}


inline const unsigned int Barrel::getScor()const
{
	return this->scor;
}

#endif