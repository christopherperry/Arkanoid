#pragma once

#include <SDL.h>
#include "Hit.h"

class Collider
{
	virtual void moveBy(int distanceX, int distanceY) = 0;

	/*
	 * Checks a collision between this collider and another.
	 * Returns the collision normal if there was a collision else
	 * returns Vector2::zero
	 */
	virtual Hit checkCollision(const Collider& other) = 0;

	virtual void render(SDL_Renderer* renderer) = 0;
};

