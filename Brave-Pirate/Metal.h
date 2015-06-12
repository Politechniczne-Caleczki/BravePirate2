#ifndef Metal_h
#define Metal_h
#pragma once
#include "BonusObject.h"
#include "Time.h"


class Metal: public BonusObject
{
private:
	
public:
	Metal(const Vector2, const Vector2, const float, const std::string , float, float);
	~Metal(void);
	void update(void);

	friend std::ostream & operator<< (std::ostream &, const Metal &);
	friend std::istream & operator>> (std::istream &, Metal &);
};

#endif
