#pragma once
#include "GameObject.h"
#include "Sea.h"


class FloatingObject :public GameObject
{
protected:
	Vector2 front, back;
	float difference;

public:	
	FloatingObject(void);
	FloatingObject(const GameObject gameobject,const Vector2 front,const Vector2 back);
	~FloatingObject(void);

	void setPositionX(const float x);
	void setPositionY(void);

	void update(void);
	void draw(void)const;
};

