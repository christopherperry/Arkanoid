#pragma once

#include <SDL.h>
#include <string>

class Spritesheet
{
private:
	std::string filename;
public:
	Spritesheet(const std::string filename);

	/**
	 * Loads an image into a texture on the rendering device.
	 *
	 * @param file The image file to load
	 * @param ren The renderer to load the texture onto
	 * @return the loaded texture, or nullptr if something went wrong.
	*/
	SDL_Texture* load(SDL_Renderer* renderer);

};