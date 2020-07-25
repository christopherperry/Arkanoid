#pragma once

#include <SDL.h>
#include "Collider.h"
#include "Vector2.h"

class AABB
{
private:
	void render(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	
	Vector2 normalLeft = Vector2::left;
	Vector2 normalRight = Vector2::right;
	Vector2 normalTop = Vector2::up;
	Vector2 normalBottom = Vector2::down;

public:
	Vector2 position;
	Vector2 extents;

	AABB(Vector2 position, Vector2 extents);
	void moveBy(float distanceX, float distanceY);

	/*
	 * Checks a collision between this box and another
	 */
	bool checkCollision(const AABB& other);

	Hit* checkIntersection(const AABB& other);

	void render(SDL_Renderer* renderer);

	void renderHit(SDL_Renderer* renderer);
};