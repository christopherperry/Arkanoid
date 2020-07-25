#pragma once

#include <map>
#include <vector>
#include "sprites/sprite.h"
#include "Entity.h"
#include "Player.h"
#include "Ball.h"

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

	// Player - Medium
	PLAYER_LEFT_MEDIUM,
	PLAYER_RIGHT_MEDIUM,
	PLAYER_LEFT_MEDIUM_DISSOLVE_1,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_1,
	PLAYER_LEFT_MEDIUM_DISSOLVE_2,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_2,
	PLAYER_LEFT_MEDIUM_DISSOLVE_3,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_3,

	// Player - Medium Gunner
	PLAYER_LEFT_MEDIUM_GUNNER,
	PLAYER_RIGHT_MEDIUM_GUNNER,

	// Player - Large
	PLAYER_LEFT_LARGE,
	PLAYER_RIGHT_LARGE,

	// Player - Small
	PLAYER_SMALL,

	// Ball
	BALL,

	NONE = -1
};


class Game
{
private:
	// The tiles are square 31x31
	static const int TILE_SIZE = 31;
	static const int OFFSET = TILE_SIZE * 0.5;
	static const int BRICK_HEIGHT = 16;
	static const int WALL_TOP_THICKNESS = 13;

	// Let's do 11 bricks and a wall on each side for now
	static const int NUM_TILES_WIDE = 13;
	static const int NUM_TILES_HIGH = 16;

	std::map<int, Sprite> sprites;
	std::vector<Entity*> entities;
public:
	Game(SDL_Texture* texture);
	Sprite* getSprite(int id);
	Player* createPlayer();
	Ball* createBall(Player* player);
	void render(SDL_Renderer* renderer);
};