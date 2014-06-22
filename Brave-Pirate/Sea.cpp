#include "Sea.h"

//Constructors and destructors

Sea::Sea(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float speed)
	:GameObject(position,size,angle,textureName),speed(speed)
{	
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
	Sea::shift = (float)((int)Sea::shift%(int)size.get_X());
}

std::ostream & operator<< (std::ostream &w, const Sea &s)
{
	return w<<s.angle<<" "<<s.seaLevel<<" "<<s.shift<<" "<<s.size
		<<" "<<s.speed<<" "<<s.textureName<<std::endl<<std::endl;
}

std::istream & operator>> (std::istream &w, Sea &s)
{
	w>>s.angle>>s.seaLevel>>s.shift>>s.size
		>>s.speed>>s.textureName;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}


Vector2 Sea::size = Vector2(0,0);
float Sea::shift = 0;
float Sea::seaLevel = 0;
float Sea::waveHeight = 0;

