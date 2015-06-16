#include "GameObject.h"

//Constructors and destructors

GameObject::GameObject(const Vector2 position, const Vector2 size, const float angle,const std::string textureName):
	position(position), 
	size(size.module()), 
	angle(angle), 
	textureName(textureName),	
	texture(Textures::getTexture(textureName)),
	_isDestroyed(false)

{
}

GameObject::~GameObject(void)
{
}

//Getters and setters


//Functions
void GameObject::draw(void)const
{
	GraphicDevice::drawTexture(texture, position, size); 
}

void GameObject::update(void)
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
	return(getCenterPosition().distance(gameObject.getCenterPosition()) < size.get_X()/2 + gameObject.size.get_X()/2);
}

Lista GameObject::getNewList(void)
{
	Lista list;
	return list;
}

const Vector2 GameObject::getCenterPosition()const
{
	return position + size/2;
}


Lista GameObject::cactosArrayPointer = GameObject::getNewList();
Lista GameObject::metalArrayPointer = GameObject::getNewList();
