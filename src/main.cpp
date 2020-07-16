#include <iostream>
#include <SDL.h>
#include <map>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "sprites/spritesheet.h"
#include "sprites/sprite.h"
#include "TextureLoader.h"
#include "sprites/SpriteRenderer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//We'll just be using square tiles for now
const int TILE_SIZE = 40;

enum SpriteId
{
	BRICK_YELLOW,
	BRICK_GREEN,
	BRICK_RED,
	BRICK_BROWN,
	BRICK_LAVENDER,
	BRICK_ORANGE,
	BRICK_BLUE,
	BRICK_PURPLE,
	BRICK_GREY_IDLE,
	BRICK_GREY_ANIM_1,
	BRICK_GRAY_ANIM_2
};

SpriteId& operator++(SpriteId& s, int)
{
	switch (s)
	{
	case BRICK_GRAY_ANIM_2:
		return s = BRICK_YELLOW;
	default:
		return s = (SpriteId)(s + 1);
	}
}

SpriteId& operator--(SpriteId& s, int)
{
	switch (s)
	{
	case BRICK_YELLOW:
		return s = BRICK_GRAY_ANIM_2;
	default:
		return s = (SpriteId)(s - 1);
	}
}

std::map<int, Sprite> defineBrickSprites()
{
	std::map<int, Sprite> bricks = {
		{BRICK_YELLOW, Sprite({225, 193, 31, 16})},
		{BRICK_GREEN, Sprite({225, 225, 31, 16})},
		{BRICK_RED, Sprite({225, 257, 31, 16})},
		{BRICK_BROWN, Sprite({225, 289, 31, 16})},
		{BRICK_LAVENDER, Sprite({257, 193, 31, 16})},
		{BRICK_ORANGE, Sprite({257, 225, 31, 16})},
		{BRICK_BLUE, Sprite({257, 257, 31, 16})},
		{BRICK_PURPLE, Sprite({257, 289, 31, 16})},
		{BRICK_GREY_IDLE, Sprite({161, 1, 31, 16})},
		{BRICK_GREY_ANIM_1, Sprite({129, 1, 31, 16})},
		{BRICK_GRAY_ANIM_2, Sprite({161, 1, 31, 16})}
	};

	return bricks;
}

// This particular signature of main is required by SDL.
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Logger::logSDLError("SDL_Init");
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

	SDL_Texture* texture = TextureLoader::load(renderer, getResourcePath() + "spritesheet.bmp"); // 640x480
	if (texture == nullptr) {
		cleanup(texture, renderer, window);
		SDL_Quit();
		return 1;
	}

	std::map<int, Sprite> bricks = defineBrickSprites();
	Spritesheet spritesheet{texture, bricks};
	SpriteRenderer spriteRenderer{renderer};

	SpriteId spriteId = SpriteId::BRICK_YELLOW;

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
				case SDLK_LEFT:
					spriteId--;
					break;
				case SDLK_RIGHT:
					spriteId++;
					break;
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

		spriteRenderer.render(spritesheet, spriteId, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);

		SDL_RenderPresent(renderer);
	}

	cleanup(texture, renderer, window);
	SDL_Quit();

	return 0;
}