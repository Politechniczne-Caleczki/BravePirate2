#pragma once
#include <math.h>
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

	const Vector2 operator=(const Vector2 &);
	const bool operator==(const Vector2 &v)const;
	const Vector2 operator-(const Vector2 &v)const;
	const Vector2 operator*(const float &v)const;
	const Vector2 operator-=(const Vector2 &);
	const Vector2 operator+(const Vector2 &)const;
	const Vector2 operator/(const float&)const;
};

