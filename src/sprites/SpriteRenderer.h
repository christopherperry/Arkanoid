#pragma once
#include "spritesheet.h"

class SpriteRenderer
{
private: 
	SDL_Renderer* renderer;
public:
	SpriteRenderer(SDL_Renderer* renderer);

	/*
	 *	Renders the sprite with the given sprite ID at the requested location.
	 *  The sprite is centered around the location.
	 */
	void render(const Spritesheet& spritesheet, int spriteId, int locationX, int locationY);
};