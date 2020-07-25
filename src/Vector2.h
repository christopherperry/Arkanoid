#pragma once

#include <utility>

class Vector2
{
public:
	float x;
	float y;

	Vector2(float x = 0.0, float y = 0.0) : x{ x }, y{ y } {};
	Vector2 operator-() const;
	float dot(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator+(const Vector2& other);
	Vector2 operator*(float scalar);

	const static Vector2 up;
	const static Vector2 down;
	const static Vector2 left;
	const static Vector2 right;
};