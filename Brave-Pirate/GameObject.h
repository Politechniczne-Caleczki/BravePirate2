#pragma once
#include <list>
#include <cstddef>
#include "Vector2.h"
#include "GraphicDevice.h"
#include "BasicObject.h"
#include "Textures.h"

class GameObject;

typedef std::list<GameObject*> Lista;

class GameObject : public BasicObject
{
private:
	static Lista getNewList();	
protected:
	std::string textureName;
	Vector2 position, size;
	float angle;
	SDL_Texture * texture;
	bool _isDestroyed; 
	void onDestroy(void);	
	bool onCollision(GameObject &gameObject)const;
public:
	static Lista fishesArrayPointer;
	static Lista barrelsArrayPointer;

	GameObject(const Vector2 position, const Vector2 size, const float angle, const std::string);
	virtual~GameObject(void);

	const Vector2 getPosition(void)const;
	const Vector2 getCenterPosition(void)const;
	const Vector2 getSize(void)const;
	SDL_Texture* getTexture(void)const;
	const float getAngle(void)const;
	void setAngle(const float angle);
	void setPosition(const Vector2 position);
	void setSize(const Vector2 size);
	void setTexture(SDL_Texture* texture);	

	virtual void draw()const;
	virtual void update();	
	 
	virtual void onCollision(void);	
	virtual void onCollision(const float strength);	
	virtual const bool isDestroyed()const;
};


inline const float GameObject::getAngle()const
{
	return this->angle;
}

inline const Vector2 GameObject::getPosition()const
{
	return this->position;
}

inline const Vector2 GameObject::getSize()const
{
	return this->size;
}

inline SDL_Texture* GameObject::getTexture()const
{
	return this->texture;
}

inline void GameObject::setAngle(const float angle)
{
	this->angle = angle;
}

inline void GameObject::setPosition(const Vector2 position)
{
	this->position = position;
}

inline void GameObject::setSize(const Vector2 size)
{
	this->size = size;
}

inline void GameObject::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

inline void GameObject::onCollision(void)
{
	_isDestroyed = true;
}

inline const bool GameObject::isDestroyed()const
{
	return _isDestroyed;
}