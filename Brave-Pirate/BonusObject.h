#ifndef BonusObject_h
#define BonusObject_h
#pragma once
#include "GameObject.h"

class BonusObject: public GameObject
{
protected:
	float speed;
	Metal_Bonus_Types type;
	float value;
public:
	BonusObject(const Vector2, const Vector2, const float, const std::string, const Metal_Bonus_Types, const float, const float);
	virtual ~BonusObject(void);

	const Metal_Bonus_Types getType()const;
	const float getValue()const;
	const float getSpeed()const;

	void setValue(const float);
	void setSpeed(const float);
	void setType(const Metal_Bonus_Types);
};

inline const Metal_Bonus_Types  BonusObject::getType()const
{
	return type;
}

inline const float BonusObject::getValue()const
{
	return value;
}

inline const float BonusObject::getSpeed()const
{
	return speed;
}

inline void BonusObject::setValue(const float value)
{
	this->value = value;
}

inline void BonusObject::setSpeed(const float speed)
{
	this->speed = speed;
}

inline void BonusObject::setType(const Metal_Bonus_Types type)
{
	this->type = type;
}

#endif