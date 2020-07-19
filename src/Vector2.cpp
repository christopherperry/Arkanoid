#include "Vector2.h"

const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::right = Vector2(1, 0);

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

inline Vector2& operator*(Vector2& v, float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	return v;
}

inline Vector2& operator*(float scalar, Vector2& v)
{
	v.x *= scalar;
	v.y *= scalar;
	return v;
}