#pragma once

#include <SDL.h>

struct Sprite
{
	/**
	 * Position and size in a Spritesheet.
	 * Used to properly render a sprite.
	 */
	SDL_Rect rect;
};