#include "Bonus.h"


Bonus::Bonus(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float value, float speed, float depth, const Metal_Bonus_Types type): 
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

std::ostream & operator<< (std::ostream &w, const Bonus &b)
{
	return w<<2<<" "<<b.angle<<" "<<b.depth<<" "<<b.position<<" "<<b.size
		<<" "<<b.speed<<" "<<b.textureName<<" "<<(int)b.type<<" "<<b.value<<std::endl;
}

std::istream & operator>> (std::istream &w, Bonus &b)
{
	int typ = 0;
	w>>b.angle>>b.depth>>b.position>>b.size
		>>b.speed>>b.textureName>>typ>>b.value;
	b.setType((Metal_Bonus_Types)typ);
	b.texture = Textures::getTexture(b.textureName);
	return w;
}
