#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "sprites/sprite.h"
#include "TextureLoader.h"
#include "Game.h"
#include "Player.h"

const float BALL_SPEED = 300.0f / 1000.0f; // pixels per second, time is in milliseconds

// The tiles are square 31x31
const int TILE_SIZE = 31;

// Let's do 11 bricks and a wall on each side for now
const int NUM_TILES_WIDE = 13;
const int NUM_TILES_HIGH = 16;

constexpr int WINDOW_WIDTH = TILE_SIZE * NUM_TILES_WIDE;
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

	Mix_Chunk* paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	Mix_Chunk* brickHit = Mix_LoadWAV("res/brick-hit.wav");
	

	Game game{ texture };
	game.loadLevel();

	Player* player = game.createPlayer();

	Ball* ball = game.createBall(player, brickHit, paddleHit);

	// Pick a random start velocity between 25 and 155 degrees
	float pi = 2 * std::acos(0);
	int randomAngle = 25 + (std::rand() % (155 - 25 + 1));
	int randomAngleRadians = randomAngle * (pi / 180.0f);
	Vector2 startVelocity = Vector2(std::cos(randomAngleRadians), -std::sin(randomAngleRadians)) * BALL_SPEED;
	ball->setVelocity(startVelocity);

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
		game.update();
		player->update(deltaTime);
		ball->update(deltaTime);

		// Check for player collisions
		std::vector<std::pair<Entity*, Hit*>> playerCollisions = game.checkCollisions(player);
		if (playerCollisions.size() > 0)
		{
			player->onCollision(playerCollisions.at(0).second);
		}

		// Check for ball collisions
		std::vector<std::pair<Entity*, Hit*>> ballCollisions = game.checkCollisions(ball);
		Hit* hitPlayer = ball->checkCollision(*player);
		if (hitPlayer != nullptr)
		{
			ball->onCollision(hitPlayer);
		}
		else
		{
			// Handle collisions
			for (std::pair<Entity*, Hit*>& collision : ballCollisions)
			{
				Entity* theThingWeHit = collision.first;
				theThingWeHit->onCollision(collision.second); // Passing this may be interpreted wrong if we decide to interpret it
				ball->onCollision(collision.second);
			}
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
		//ball->renderColliders(renderer);

		// Render collisions for debugging
		for (std::pair<Entity*, Hit*>& collision : ballCollisions)
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

	Mix_FreeChunk(paddleHit);
	Mix_FreeChunk(brickHit);
	Mix_Quit();
	SDL_Quit();

	return 0;
}