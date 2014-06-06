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

//Getters and setters
float Vector2::get_X(void)const
{
	return this->x;
}

float Vector2::get_Y(void)const
{
	return this->y;
}

void Vector2::set_X(const float x)
{
	this->x = x;
}

void Vector2::set_Y(const float y)
{
	this->y = y;
}

//Functions
const float Vector2::distance(const Vector2 & vector2)const
{
	float x1 = (x - vector2.x);
	float y1 = (y - vector2.y);
	return sqrt((x1 * x1) + (y1 * y1));
}

const float Vector2::angleRad(const Vector2 & vector2)const
{
	return atan2(vector2.y - y, vector2.x - x);
}

const float Vector2::angleDeg(const Vector2 & vector2)const
{
	return  (float)(angleRad(vector2) * 180 / PI);
}


const Vector2 Vector2::module(void)const
{ 
	return Vector2(fabs(x), fabs(y));
}

const Vector2 Vector2::operator=(const Vector2 &vector2)
{
	this->x = vector2.x;
	this->y = vector2.y;

	return * this;
}

const bool Vector2::operator==(const Vector2 &vector2)const
{
	return ((x == vector2.x) && (y == vector2.y));
}

const Vector2 Vector2::operator-(const Vector2 &vector2)const
{
	return Vector2(x - vector2.x, y - vector2.y);
}

const Vector2 Vector2::operator+(const Vector2 &vector2)const
{
	return Vector2(x + vector2.x, y + vector2.y);
}

 const Vector2 Vector2::operator-=(const Vector2 &vector2)
{
	this->x -= vector2.x;
	this->y -= vector2.y;
	return * this;
}

 const Vector2 Vector2::operator/(const float & value)const
{
	if(value!=0)
		return Vector2(x /value, y /value);
	else
		return Vector2(x, y);
}


