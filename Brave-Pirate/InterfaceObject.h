#pragma once
#include "BasicObject.h"
#include "Vector2.h"

class InterfaceObject : public BasicObject
{
protected:
	Vector2 position, size;

public:
	InterfaceObject(const Vector2 ,const Vector2);
	~InterfaceObject(void);


	void setPosition(const Vector2 position);
	void setSize(const Vector2 size);

	const Vector2 getPosition(void)const;
	const Vector2 getCenterPosition(void)const;
	const Vector2 getSize(void)const;
};

