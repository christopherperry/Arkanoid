#include "ExpandCapsule.h"

ExpandCapsule::ExpandCapsule(SDL_Texture* texture, Vector2 position) : PowerUpCapsule(position)
{
	sprites = {
		{ 0, new Sprite{texture, SDL_Rect{485, 161, 23, 11}} },
		{ 1, new Sprite{texture, SDL_Rect{485, 193, 23, 11}} },
		{ 2, new Sprite{texture, SDL_Rect{485, 225, 23, 11}} },
		{ 3, new Sprite{texture, SDL_Rect{485, 257, 23, 11}} },
		{ 4, new Sprite{texture, SDL_Rect{485, 289, 23, 11}} },
		{ 5, new Sprite{texture, SDL_Rect{485, 321, 23, 11}} },
		{ 6, new Sprite{texture, SDL_Rect{485, 353, 23, 11}} }
	};
}