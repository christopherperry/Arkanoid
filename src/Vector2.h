#pragma once

class Vector2
{
public:
	float x{0.0};
	float y{0.0};

	Vector2(float x, float y) : x(x), y(y) {};
	Vector2(const Vector2& other) = default;
	Vector2& operator=(const Vector2& other);

	const static Vector2 up;
	const static Vector2 down;
	const static Vector2 left;
	const static Vector2 right;
};

inline Vector2& operator*(Vector2& v, float scalar);
inline Vector2& operator*(float scalar, Vector2& v);