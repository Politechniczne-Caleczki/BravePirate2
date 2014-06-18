#pragma once
#include "FloatingObject.h"


class Barrel : public FloatingObject
{
private:
	float health, speed, damage;	

public:
	Barrel(const FloatingObject & floatingObject, const float health, const float speed, const float damage);
	~Barrel(void);

	void decreaseHealth(const float decreaseValue);
	void update(void);
	void onCollision(void);
	void onCollision(const float strength);
	inline const float getDamage()const;
	inline const bool isDestroed()const;

};

inline void Barrel::onCollision(void)
{
	_isDestroyed= true;
}

inline const float Barrel::getDamage()const
{
	return this->damage;
}
