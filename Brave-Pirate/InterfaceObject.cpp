#include "InterfaceObject.h"


InterfaceObject::InterfaceObject(const Vector2 position,const Vector2 size):position(position), size(size.module()){}


InterfaceObject::~InterfaceObject(void)
{
}

const Vector2 InterfaceObject::getCenterPosition()const
{
	return position + size/2;
}

void InterfaceObject::setPosition(const Vector2 position)
{
	this->position = position;
}

void InterfaceObject::setSize(const Vector2 size)
{
	this->size = size;
}

const Vector2 InterfaceObject::getPosition()const
{
	return this->position;
}

const Vector2 InterfaceObject::getSize()const
{
	return this->size;
}