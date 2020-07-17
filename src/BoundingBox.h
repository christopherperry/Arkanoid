#pragma once

#include <SDL.h>

class BoundingBox
{
private:
	/*
	 * Position and bounding area of the box.
	 * Position is top left of the box.
	 */
	SDL_Rect bounds;

public:
	BoundingBox();
	BoundingBox(SDL_Rect bounds);
	void moveTo(SDL_Point position);
	bool collidesWith(BoundingBox& other);
	void render(SDL_Renderer* renderer);
};

