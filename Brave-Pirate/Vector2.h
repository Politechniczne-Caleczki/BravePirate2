#pragma once
#include <math.h>
#include <iostream>
#define PI 3.14159265358979323846

class Vector2
{
private:
	float x, y;
public:
	Vector2(void);
	~Vector2(void);
	Vector2(const float x, const float y);

	float get_X(void)const;
	float get_Y(void)const;
	void set_X(const float x);
	void set_Y(const float y);

	const float distance(const Vector2 &)const;
	const float angleRad(const Vector2 &)const;
	const float angleDeg(const Vector2 &)const;
	const Vector2 module(void)const;

	const Vector2 operator= (const Vector2 & );
	const bool    operator==(const Vector2 &v)const;
	const Vector2 operator- (const Vector2 & )const;
	const Vector2 operator* (const float &   )const;
	const Vector2 operator-=(const Vector2 & );
	const Vector2 operator+ (const Vector2 & )const;
	const Vector2 operator/ (const float&)const;
	friend std::ostream & operator<< (std::ostream &, const Vector2 &);
	friend std::istream & operator>> (std::istream &wejscie, Vector2 &);
};

//Getters and setters
inline float Vector2::get_X(void)const
{
	return this->x;
}

inline float Vector2::get_Y(void)const
{
	return this->y;
}

inline void Vector2::set_X(const float x)
{
	this->x = x;
}

inline void Vector2::set_Y(const float y)
{
	this->y = y;
}

//Functions
inline const float Vector2::distance(const Vector2 & vector2)const
{
	float x1 = (x - vector2.x);
	float y1 = (y - vector2.y);
	return sqrt((x1 * x1) + (y1 * y1));
}

inline const float Vector2::angleRad(const Vector2 & vector2)const
{
	return atan2(vector2.y - y, vector2.x - x);
}

inline const float Vector2::angleDeg(const Vector2 & vector2)const
{
	return  (float)(angleRad(vector2) * 180 / PI);
}

inline const Vector2 Vector2::module(void)const
{ 
	return Vector2(fabs(x), fabs(y));
}

inline const Vector2 Vector2::operator=(const Vector2 &vector2)
{
	this->x = vector2.x;
	this->y = vector2.y;

	return * this;
}

inline const bool Vector2::operator==(const Vector2 &vector2)const
{
	return ((x == vector2.x) && (y == vector2.y));
}

inline const Vector2 Vector2::operator-(const Vector2 &vector2)const
{
	return Vector2(x - vector2.x, y - vector2.y);
}

inline const Vector2 Vector2::operator+(const Vector2 &vector2)const
{
	return Vector2(x + vector2.x, y + vector2.y);
}

inline const Vector2 Vector2::operator-=(const Vector2 &vector2)
{
	this->x -= vector2.x;
	this->y -= vector2.y;
	return * this;
}

inline const Vector2 Vector2::operator/(const float & value)const
{
	if(value!=0)
		return Vector2(x /value, y /value);
	else
		return Vector2(x, y);
}

inline const Vector2 Vector2::operator*(const float & value)const
{
	return Vector2(x*value, y*value);
}

