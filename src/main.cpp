#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "TextureLoader.h"
#include "Game.h"

// The tiles are square 31x31
const int TILE_SIZE = 31;

// Let's do 11 bricks and a wall on each side for now
const int NUM_TILES_WIDE = 13;
const int NUM_TILES_HIGH = 16;

constexpr int WINDOW_WIDTH = TILE_SIZE * (NUM_TILES_WIDE + 4);
constexpr int WINDOW_HEIGHT = TILE_SIZE * NUM_TILES_HIGH;

// This particular signature of main is required by SDL.
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Create the game and load the level
	Game game{ renderer, texture };
	game.loadLevel();

	//Our event structure
	SDL_Event e;
	bool quit = false;
	bool moveLeft = false;
	bool moveRight = false;

	// Time
	float deltaTime = 0;
	float lastFrameTime = SDL_GetTicks();

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

			game.onEvent(e);
		}

		// Update
		game.update(deltaTime);

		// Collisions
		game.checkCollisions();

		///////////////////
		// RENDERING BEGIN
		//////////////////

		// Clear the scene
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		game.render();

		// Present all the render calls
		SDL_RenderPresent(renderer);

		///////////////////
		// RENDERING END
		//////////////////

		// Update time
		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
	}

	cleanup(texture, renderer, window);

	Mix_Quit();
	SDL_Quit();

	return 0;
}