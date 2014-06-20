#pragma once
#include "BonusObject.h"
#include "Time.h"

class Bonus:public BonusObject
{
private: 
	float depth;
public:
	Bonus(const Vector2, const Vector2, const float, const std::string , float, float, float, const Fishs_Gifts_Types);
	~Bonus(void);
	void update(void);

	friend std::ostream & operator<< (std::ostream &, const Bonus &);
	friend std::istream & operator>> (std::istream &, Bonus &);
};

