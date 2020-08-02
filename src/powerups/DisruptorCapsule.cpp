#include "DisruptorCapsule.h"

DisruptorCapsule::DisruptorCapsule(SDL_Texture* texture, Vector2 position) : PowerUpCapsule(position)
{
	sprites = {
		{ 0, new Sprite{texture, SDL_Rect{581, 1, 23, 11}} },
		{ 1, new Sprite{texture, SDL_Rect{581, 33, 23, 11}} },
		{ 2, new Sprite{texture, SDL_Rect{581, 65, 23, 11}} },
		{ 3, new Sprite{texture, SDL_Rect{581, 97, 23, 11}} },
		{ 4, new Sprite{texture, SDL_Rect{581, 129, 23, 11}} },
		{ 5, new Sprite{texture, SDL_Rect{581, 161, 23, 11}} },
		{ 6, new Sprite{texture, SDL_Rect{581, 193, 23, 11}} }
	};
}