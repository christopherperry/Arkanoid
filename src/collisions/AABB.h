#pragma once

#include <SDL.h>
#include "Hit.h"
#include "../math/Vector2.h"

class AABB
{
private:
	void render(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	
	Vector2 normalLeft{ Vector2::left };
	Vector2 normalRight{ Vector2::right };
	Vector2 normalTop{ Vector2::up };
	Vector2 normalBottom{ Vector2::down };

public:
	Vector2 position;
	Vector2 extents;

	AABB(Vector2 position, Vector2 extents);
	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;

	void moveBy(float distanceX, float distanceY);
	void moveTo(Vector2 position);

	/*
	 * Checks a collision between this box and another
	 */
	bool checkCollision(const AABB& other) const;

	Hit* checkIntersection(const AABB& other) const;

	void render(SDL_Renderer* renderer) const;

	void renderHit(SDL_Renderer* renderer) const;
};