#ifndef FloatingObject_h
#define FloatingObject_h
#pragma once
#include "Sea.h"


class FloatingObject : public GameObject
{
protected:
	Vector2 front, back;
	float difference;

public:	
	FloatingObject(const Vector2, const Vector2, const float, const std::string , const Vector2,const Vector2);
	virtual~FloatingObject(void);

	void setPositionX(const float x);
	void setPositionY(void);

	virtual void update(void);
	virtual void draw(void)const;
};

#endif