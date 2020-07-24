#pragma once

#include <SDL.h>
#include "Collider.h"
#include "Vector2.h"

class AABB
{
private:
	
	Vector2 normalLeft = Vector2::left;
	Vector2 normalRight = Vector2::right;
	Vector2 normalTop = Vector2::up;
	Vector2 normalBottom = Vector2::down;

public:
	Vector2 position;
	Vector2 extents;

	AABB(Vector2 position, Vector2 extents);
	void moveBy(int distanceX, int distanceY);

	/*
	 * Checks a collision between this box and another
	 */
	bool checkCollision(const AABB& other);

	void render(SDL_Renderer* renderer);
};