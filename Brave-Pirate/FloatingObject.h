#pragma once
#include "GameObject.h"
#include "Sea.h"


class FloatingObject : public GameObject
{
protected:
	Vector2 front, back;
	float difference;

public:	
	FloatingObject(const Vector2 position, const Vector2 size, const float angle, SDL_Texture* texture, const Vector2 front,const Vector2 back);
	~FloatingObject(void);

	void setPositionX(const float x);
	void setPositionY(void);

	void update(void);
	void draw(void)const;
};

