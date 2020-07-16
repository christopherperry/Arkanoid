#pragma once

#include <SDL.h>

class TextureLoader
{
public:
	static SDL_Texture* load(SDL_Renderer* renderer, const std::string& filename);
};

