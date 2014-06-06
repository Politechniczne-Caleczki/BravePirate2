#include "GameObject.h"

//Constructors and destructors
GameObject::GameObject(void):position(Vector2(0,0)),scale(Vector2(0,0)),angle(0), texture(NULL)
{
}

GameObject::GameObject(const Vector2 position, const Vector2 scale, const float angle,SDL_Texture* texture):
	position(position), 
	scale(scale.module()), 
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

Vector2 GameObject::getPosition()const
{
	return this->position;
}

Vector2 GameObject::getScale()const
{
	return this->scale;
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

void GameObject::setScale(const Vector2 scale)
{
	this->scale = scale;
}

void GameObject::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

//Functions
void GameObject::draw(void)const
{
	GraphicDevice::drawTexture(texture, position, scale); 
}

void GameObject::update(void)
{
}

void GameObject::onCollision(void)
{
}

void GameObject::onCollision(const float strength)
{
}

void GameObject::onDestroy(void)
{
}

bool GameObject::onCollision(GameObject &gameObject)const
{
	return(getCenterPosition().distance(gameObject.getCenterPosition()) < scale.get_X()/2 + gameObject.scale.get_X()/2);
}

Lista GameObject::getNewList(void)
{
	Lista list;
	return list;
}

bool GameObject::isDestroyed()const
{
	return _isDestroyed;
}

Vector2 GameObject::getCenterPosition()const
{
	return position + scale/2;
}



Lista GameObject::barrelsArrayPointer = GameObject::getNewList();
Lista GameObject::fishesArrayPointer = GameObject::getNewList();