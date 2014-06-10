#include "GameObject.h"

//Constructors and destructors

GameObject::GameObject(const Vector2 position, const Vector2 size, const float angle,SDL_Texture* texture):
	position(position), 
	size(size.module()), 
	angle(angle), 
	texture(texture),
	_isDestroyed(false)

{
}

GameObject::~GameObject(void)
{
}

//Getters and setters
float GameObject::getAngle()const
{
	return this->angle;
}

const Vector2 GameObject::getPosition()const
{
	return this->position;
}

const Vector2 GameObject::getSize()const
{
	return this->size;
}

SDL_Texture* GameObject::getTexture()const
{
	return this->texture;
}

void GameObject::setAngle(const float angle)
{
	this->angle = angle;
}

void GameObject::setPosition(const Vector2 position)
{
	this->position = position;
}

void GameObject::setSize(const Vector2 size)
{
	this->size = size;
}

void GameObject::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

//Functions
void GameObject::draw(void)const
{
	GraphicDevice::drawTexture(texture, position, size); 
}

void GameObject::update(void)
{
}


void GameObject::onCollision(void)
{
	_isDestroyed = true;
}

void GameObject::onCollision(const float strength)
{
}

void GameObject::onDestroy(void)
{
}

bool GameObject::onCollision(GameObject &gameObject)const
{
	return(getCenterPosition().distance(gameObject.getCenterPosition()) < size.get_X()/2 + gameObject.size.get_X()/2);
}

Lista GameObject::getNewList(void)
{
	Lista list;
	return list;
}

const bool GameObject::isDestroyed()const
{
	return _isDestroyed;
}

const Vector2 GameObject::getCenterPosition()const
{
	return position + size/2;
}



Lista GameObject::barrelsArrayPointer = GameObject::getNewList();
Lista GameObject::fishesArrayPointer = GameObject::getNewList();