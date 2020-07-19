#include <iostream>
#include <SDL.h>
#include <map>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "sprites/sprite.h"
#include "TextureLoader.h"
#include "Game.h"
#include "Player.h"

// The tiles are square 31x31
const int TILE_SIZE = 31;

// Let's do 11 bricks and a wall on each side for now
const int NUM_TILES_WIDE = 13;
const int NUM_TILES_HIGH = 16;

constexpr int WINDOW_WIDTH = TILE_SIZE * NUM_TILES_WIDE;
constexpr int WINDOW_HEIGHT = TILE_SIZE * NUM_TILES_HIGH;


void renderSprite(SDL_Renderer* renderer, Sprite* sprite, int positionX, int positionY)
{
	SDL_Rect location;
	location.x = positionX;
	location.y = positionY;
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}

// This particular signature of main is required by SDL.
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		Logger::logSDLError("SDL_Init");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Arinoid: Revenge of Ari", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

	Game game{ texture };
	Player* player = game.createPlayer();
	SpriteId spriteId = SpriteId::BRICK_YELLOW;

	//Our event structure
	SDL_Event e;
	bool quit = false;
	bool moveLeft = false;
	bool moveRight = false;

	while (!quit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}

			player->onEvent(e);
		}

		player->update();

		// Clear the scene
		SDL_RenderClear(renderer);

		// Render
		game.render(renderer);
		player->render(renderer);

		// Render the scene
		SDL_RenderPresent(renderer);
	}

	delete player;
	cleanup(texture, renderer, window);
	SDL_Quit();

	return 0;
}