#include <iostream>
#include <SDL.h>
#include <map>
#include "resources.h"
#include "cleanup.h"
#include "logger.h"
#include "sprites/sprite.h"
#include "TextureLoader.h"


// The tiles are square 31x31
const int TILE_SIZE = 31;

// Let's do 11 bricks and a wall on each side for now
const int NUM_TILES_WIDE = 13;
const int NUM_TILES_HIGH = 16;

constexpr int WINDOW_WIDTH = TILE_SIZE * NUM_TILES_WIDE;
constexpr int WINDOW_HEIGHT = TILE_SIZE * NUM_TILES_HIGH;

enum SpriteId
{
	// Bricks
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
	BRICK_GRAY_ANIM_2,

	// Walls
	WALL_CORNER_TOP_LEFT,
	WALL_CORNER_TOP_RIGHT,
	WALL_LEFT_STRAIGHT,
	WALL_LEFT_RIVETED,
	WALL_RIGHT_STRAIGHT,
	WALL_RIGHT_RIVETED,
	WALL_TOP_PLAIN,
	WALL_TOP_RIVETED,
	WALL_TOP_EMITER_IDLE,
	WALL_TOP_EMITER_ANIM_1,
	WALL_TOP_EMITER_ANIM_2,
	WALL_TOP_EMITER_OPEN,

	// Backgrounds
	BACKGROUND_DARK_PURPLE
};

SpriteId& operator++(SpriteId& s, int)
{
	switch (s)
	{
	case WALL_TOP_EMITER_OPEN:
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
		return s = WALL_TOP_EMITER_OPEN;
	default:
		return s = (SpriteId)(s - 1);
	}
}

std::map<int, Sprite> defineSprites(SDL_Texture* texture)
{
	std::map<int, Sprite> sprites = {
		// Bricks
		{BRICK_YELLOW, Sprite{texture, {225, 193, 31, 16}} },
		{BRICK_GREEN, Sprite{texture, {225, 225, 31, 16}} },
		{BRICK_RED, Sprite{texture, {225, 257, 31, 16}} },
		{BRICK_BROWN, Sprite{texture, {225, 289, 31, 16}} },
		{BRICK_LAVENDER, Sprite{texture, {257, 193, 31, 16}} },
		{BRICK_ORANGE, Sprite{texture, {257, 225, 31, 16}} },
		{BRICK_BLUE, Sprite{texture, {257, 257, 31, 16}} },
		{BRICK_PURPLE, Sprite{texture, {257, 289, 31, 16}} },
		{BRICK_GREY_IDLE, Sprite{texture, {161, 1, 31, 16}} },
		{BRICK_GREY_ANIM_1, Sprite{texture, {129, 1, 31, 16}} },
		{BRICK_GRAY_ANIM_2, Sprite{texture, {161, 1, 31, 16}} },

		// Walls
		{WALL_CORNER_TOP_LEFT, Sprite{texture, {129, 193, 31, 31}} },
		{WALL_CORNER_TOP_RIGHT, Sprite{texture, {193, 193, 31, 31}} },
		{WALL_LEFT_STRAIGHT, Sprite{texture, {129, 257, 31, 31}} },
		{WALL_LEFT_RIVETED, Sprite{texture, {129, 225, 31, 31}} },
		{WALL_RIGHT_STRAIGHT, Sprite{texture, {193, 257, 31, 31}} },
		{WALL_RIGHT_RIVETED, Sprite{texture, {193, 225, 31, 31}} },
		{WALL_TOP_PLAIN, Sprite{texture, {193, 289, 31, 31}} },
		{WALL_TOP_RIVETED, Sprite{texture, {129, 289, 31, 31}} },

		// Wall top emiter 
		{WALL_TOP_EMITER_IDLE, Sprite{texture, {161, 289, 31, 31}} },
		{WALL_TOP_EMITER_ANIM_1, Sprite{texture, {161, 257, 31, 31}} },
		{WALL_TOP_EMITER_ANIM_2, Sprite{texture, {161, 225, 31, 31}} },
		{WALL_TOP_EMITER_OPEN, Sprite{texture, {161, 193, 31, 31}} },

		// Background
		{BACKGROUND_DARK_PURPLE, Sprite{texture, {161, 321, 31, 31}} },
	};

	return sprites;
}

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

	SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

	std::map<int, Sprite> sprites = defineSprites(texture);

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

		renderSprite(renderer, &sprites[spriteId], WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);

		SDL_RenderPresent(renderer);
	}

	cleanup(texture, renderer, window);
	SDL_Quit();

	return 0;
}