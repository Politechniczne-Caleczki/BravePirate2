#include "Desert.h"

//Constructors and destructors

Desert::Desert(const Vector2 position, const Vector2 size, const float angle, const std::string textureName, float speed)
	:GameObject(position,size,angle,textureName),speed(speed)
{	
	Desert::size = GameObject::size;
}

Desert::~Desert(void)
{
}

//Functions
void Desert::draw(void)const
{
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + shift , position.get_Y()), size); 
	GraphicDevice::drawTexture(texture, Vector2(position.get_X() + size.get_X() +shift , position.get_Y()), size); 
}

void Desert::update(void)
{	
	Desert::shift -= Time::deltaTime()*speed;
	Desert::shift = (float)((int)Desert::shift%(int)size.get_X());
}

std::ostream & operator<< (std::ostream &w, const Desert &s)
{
	return w<<s.angle<<" "<<s.seaLevel<<" "<<s.shift<<" "<<s.size
		<<" "<<s.speed<<" "<<s.textureName<<std::endl<<std::endl;
}

std::istream & operator>> (std::istream &w, Desert &s)
{
	w>>s.angle>>s.seaLevel>>s.shift>>s.size
		>>s.speed>>s.textureName;
	s.texture = Textures::getTexture(s.textureName);
	return w;
}


Vector2 Desert::size = Vector2(0,0);
float Desert::shift = 0;
float Desert::seaLevel = 0;
float Desert::waveHeight = 0;

