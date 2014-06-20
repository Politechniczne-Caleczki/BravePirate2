#include "BonusObject.h"


BonusObject::BonusObject(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, const Fishs_Gifts_Types type, const float value, const float speed)
	:GameObject(position, size, angle, textureName), type(type), value(value), speed(speed){}


BonusObject::~BonusObject(void)
{
}
