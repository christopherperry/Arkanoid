#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "sprites/spritesheet.h"
#include "sprites/sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//We'll just be using square tiles for now
const int TILE_SIZE = 40;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Logger::logSDLError("SDL_Init");
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Logger::logSDLError("IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		Logger::logSDLError("SDL_CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cleanup(window);
		Logger::logSDLError("SDL_CreateRenderer");
		SDL_Quit();
		return 1;
	}

	const std::string resourcePath = getResourcePath();
	Spritesheet spritesheet(resourcePath + "spritesheet.bmp"); // 640x480
	SDL_Texture* spritesheetTexture = spritesheet.load(renderer);
	if (spritesheetTexture == nullptr) {
		cleanup(spritesheetTexture, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	//Our event structure
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		//Render the scene
		SDL_RenderClear(renderer);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 640;
		rect.h = 480;
		Sprite sprite(renderer, spritesheetTexture, rect);
		sprite.render(0, 0);

		SDL_RenderPresent(renderer);
	}

	cleanup(spritesheetTexture, renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}