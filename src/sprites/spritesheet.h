#pragma once

#include <SDL.h>
#include <map>
#include "sprite.h"

struct Spritesheet
{
	SDL_Texture* texture;
	std::map<int, Sprite> sprites;
};