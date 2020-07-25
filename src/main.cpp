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

	float ballSpeed = 100.0f / 1000.0f; // pixels per second, time is in milliseconds

	Game game{ texture };
	Player* player = game.createPlayer();
	Ball* ball = game.createBall(player);
	ball->setVelocity(Vector2{ 0, -ballSpeed });
	SpriteId spriteId = SpriteId::BRICK_YELLOW;

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

			player->onEvent(e);
		}

		// Update
		player->update(deltaTime);
		ball->update(deltaTime);

		// Check for collisions
		std::vector<std::pair<Entity*, Hit*>> collisions = game.checkCollisions(ball);
		Hit* hitPlayer = ball->checkCollision(*player);
		if (hitPlayer != nullptr)
		{
			ball->onCollision(hitPlayer);
		}

		// Handle collisions
		for (std::pair<Entity*, Hit*>& collision : collisions)
		{
			ball->onCollision(collision.second);
		}

		///////////////////
		// RENDERING BEGIN
		//////////////////

		// Clear the scene
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		game.render(renderer);
		player->render(renderer);
		//player->renderColliders(renderer);
		ball->render(renderer);
		ball->renderColliders(renderer);

		// Render collisions for debugging
		for (std::pair<Entity*, Hit*>& collision : collisions)
		{
			collision.first->renderCollidersHit(renderer);
		}

		// Render the scene
		SDL_RenderPresent(renderer);

		///////////////////
		// RENDERING END
		//////////////////

		// Update time
		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
	}

	delete player;
	cleanup(texture, renderer, window);
	SDL_Quit();

	return 0;
}