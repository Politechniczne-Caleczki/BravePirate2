#pragma once
#include "GameObject.h"

class BonusObject: public GameObject
{
protected:
	Fishs_Gifts_Types type;
	float value, speed;
public:
	BonusObject(const Vector2, const Vector2, const float, const std::string, const Fishs_Gifts_Types, const float, const float);
	virtual ~BonusObject(void);

	const Fishs_Gifts_Types getType()const;
	const float getValue()const;
	const float getSpeed()const;

	void setValue(const float);
	void setSpeed(const float);
	void setType(const Fishs_Gifts_Types);
};

inline const Fishs_Gifts_Types  BonusObject::getType()const
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

inline void BonusObject::setType(const Fishs_Gifts_Types type)
{
	this->type = type;
}

