#pragma once

#include <iostream>
#include <SDL.h>
#include "spritesheet.h"
#include "../logger.h"

Spritesheet::Spritesheet(const std::string filename)
{
	this->filename = filename;
}

//SDL_Texture* Spritesheet::load(SDL_Renderer* renderer)
//{
//	SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
//	if (texture == nullptr) {
//		Logger::logSDLError("LoadTexture");
//	}
//	return texture;
//}

SDL_Texture* Spritesheet::load(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
	if (surface == nullptr) {
		Logger::logSDLError("IMG_Load");
	}

	// Make black pixels transparent
	Uint8 r{0};
	Uint8 g{0};
	Uint8 b{0};
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		Logger::logSDLError("SDL_CreateTextureFromSurface");
	}

	SDL_FreeSurface(surface);

	return texture;
}