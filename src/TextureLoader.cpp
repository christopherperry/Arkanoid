#include <SDL.h>
#include <string>
#include "TextureLoader.h"
#include "utils/Logger.h"

SDL_Texture* TextureLoader::load(SDL_Renderer* renderer, const std::string& filename)
{
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
	if (surface == nullptr) {
		Logger::logSDLError("IMG_Load");
	}

	// Make black pixels transparent
	Uint8 r{ 0 };
	Uint8 g{ 0 };
	Uint8 b{ 0 };
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		Logger::logSDLError("SDL_CreateTextureFromSurface");
	}

	SDL_FreeSurface(surface);

	return texture;
}
