#include "Vector2.h"

//Constructors and destructors
Vector2::Vector2(void): x(0), y(0)
{
}

Vector2::Vector2(const float x, const float y): x(x), y(y)
{
}

Vector2::~Vector2(void)
{
}

std::ostream & operator<< (std::ostream & w, const Vector2 &v)
{
	return w<<v.x<<" "<<v.y<<" ";
}

std::istream & operator>> (std::istream &w, Vector2 & v)
{
	w>>v.x>>v.y;
	return w;
}