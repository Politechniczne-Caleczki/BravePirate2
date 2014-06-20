#include "Sea.h"

//Constructors and destructors

Sea::Sea(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float speed):GameObject(position,size,angle,textureName),speed(speed)
{
	Sea::position = GameObject::position;
	Sea::size = GameObject::size;
}

Sea::~Sea(void)
{
}

//Functions
void Sea::draw(void)const
{
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + shift , position.get_Y()), size); 
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + size.get_X() +shift , position.get_Y()), size); 
}

void Sea::update(void)
{	
	Sea::shift -= Time::deltaTime()*speed;
	Sea::shift = (int)Sea::shift%(int)size.get_X();
}


Vector2 Sea::position = Vector2(0,0);
Vector2 Sea::size = Vector2(0,0);
float Sea::shift = 0;

std::ostream & operator<< (std::ostream &w, const Sea &s)
{
	return w<<s.angle<<" "<<s.position<<" "<<s.shift<<" "<<s.size
		<<" "<<s.speed<<" "<<s.speed<<" "<<s.textureName<<" ";
}

std::istream & operator>> (std::istream &w, Sea &s)
{
	w>>s.angle>>s.position>>s.shift>>s.size
		>>s.speed>>s.speed>>s.textureName;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}