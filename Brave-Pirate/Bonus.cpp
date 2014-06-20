#include "Bonus.h"


Bonus::Bonus(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float value, float speed, float depth, const Fishs_Gifts_Types type): 
BonusObject(position, size, angle, textureName, type, value, speed), depth(fabs(depth))
{
	if(depth>GraphicDevice::getInstance().getWindowSize().get_Y())
		depth = GraphicDevice::getInstance().getWindowSize().get_Y();
}

Bonus::~Bonus(void)
{
}


void Bonus::update()
{
	position.set_X(position.get_X()- (speed* Time::deltaTime()));

	if(position.get_Y()<depth)
		position.set_Y(position.get_Y()+ (speed* Time::deltaTime()));
}

