#include "Vector2.h"

const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::zero = Vector2(0, 0);

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

float Vector2::dot(const Vector2& other)
{
	return (x * other.x) + (y * other.y);
}

float Vector2::magnitude()
{
	return sqrt(squareMagnitude());
}

float Vector2::squareMagnitude()
{
	return (x * x) + (y * y);
}

Vector2 Vector2::normalized()
{
	return *this * (1.0f / magnitude());
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return  Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator*(float scalar)
{
	return Vector2(scalar * x, scalar * y);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}
