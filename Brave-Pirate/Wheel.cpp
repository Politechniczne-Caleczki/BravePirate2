#include "Wheel.h"


Wheel::Wheel(GameObject gameObject) :GameObject(gameObject)
{
	circuit = 2 * PI * this->size.get_X();
}


Wheel::~Wheel()
{
}

void Wheel::update()
{
	this->angle -= 360 * (Desert::getDelta() / this->circuit);
}


void Wheel::draw()const
{
	GraphicDevice::drawTexture(this->texture, this->position, this->size, this->angle);
}


