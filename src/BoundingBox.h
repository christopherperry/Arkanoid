#pragma once

#include <SDL.h>

class BoundingBox
{
public:
	/*
	 * Position and bounding area of the box.
	 * Position is top left of the box.
	 */
	SDL_Rect bounds;

	BoundingBox(SDL_Rect bounds);
	bool collidesWith(BoundingBox& other);
	void render(SDL_Renderer* renderer);
};

