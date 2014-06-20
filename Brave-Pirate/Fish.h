#pragma once
#include "BonusObject.h"
#include "Time.h"


class Fish: public BonusObject
{
private:
	
public:
	Fish(const Vector2, const Vector2, const float, const std::string , float, float);
	~Fish(void);
	void update(void);

	friend std::ostream & operator<< (std::ostream &, const Fish &);
	friend std::istream & operator>> (std::istream &, Fish &);
};
