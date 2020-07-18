#pragma once

#include <map>
#include <vector>
#include "sprites/sprite.h"
#include "Entity.h"

// WARNING: only add at the end 
// because we hardcoded numbers to define the level
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
	BACKGROUND_BLUE, 

	NONE = -1
};


class Game
{
private:
	// The tiles are square 31x31
	static const int TILE_SIZE = 31;
	static const int BRICK_HEIGHT = 16;

	// Let's do 11 bricks and a wall on each side for now
	static const int NUM_TILES_WIDE = 13;
	static const int NUM_TILES_HIGH = 16;

	std::map<int, Sprite> sprites;
	std::vector<Entity> entities;
public:
	Game(SDL_Texture* texture);
	Sprite* getSprite(int id);
	void render(SDL_Renderer* renderer);
};

