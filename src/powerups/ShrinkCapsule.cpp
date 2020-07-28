#include "ShrinkCapsule.h"

ShrinkCapsule::ShrinkCapsule(SDL_Texture* texture, Vector2 position) : PowerUpCapsule(position)
{
	sprites = {
		{ 0, new Sprite{texture, SDL_Rect{5, 193, 23, 11}} },
		{ 1, new Sprite{texture, SDL_Rect{5, 225, 23, 11}} },
		{ 2, new Sprite{texture, SDL_Rect{5, 257, 23, 11}} },
		{ 3, new Sprite{texture, SDL_Rect{5, 289, 23, 11}} },
		{ 4, new Sprite{texture, SDL_Rect{5, 321, 23, 11}} },
		{ 5, new Sprite{texture, SDL_Rect{5, 353, 23, 11}} },
		{ 6, new Sprite{texture, SDL_Rect{5, 385, 23, 11}} }
	};
}