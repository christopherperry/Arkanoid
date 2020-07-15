#pragma once

#include <iostream>
#include <SDL_image.h>
#include "spritesheet.h"
#include "../logger.h"

Spritesheet::Spritesheet(const std::string filename)
{
	this->filename = filename;
}

SDL_Texture* Spritesheet::load(SDL_Renderer* renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
	if (texture == nullptr) {
		Logger::logSDLError("LoadTexture");
	}
	return texture;
}