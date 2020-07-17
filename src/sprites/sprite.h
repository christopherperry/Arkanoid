#pragma once

#include <SDL.h>

struct Sprite
{
	/*
	 * The texture containing the sprite.
	 */
	SDL_Texture* texture;

	/**
	 * Position and size in the texture for rendering this sprite.
	 */
	SDL_Rect rect;
};