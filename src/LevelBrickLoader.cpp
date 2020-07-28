#include <vector>
#include "LevelBrickLoader.h"
#include "collisions/AABB.h"
#include "entities/Entity.h"
#include "math/Vector2.h"
#include "entities/BackgroundTile.h"
#include "entities/Brick.h"
#include "entities/Wall.h"
#include "entities/WallCollider.h"

enum BrickId
{
	NONE,

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

};

std::vector<std::vector<int>> levelOneBricks()
{
	std::vector<std::vector<int>> levelOneBricks =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 0},
		{0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
		{0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 0},
		{0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	return levelOneBricks;
}

LevelBrickLoader::LevelBrickLoader(SDL_Texture* texture)
{
	// We create all of the sprites once and use them to render the level
	// we are asked to render.

	sprites = {
		// Bricks
		{BRICK_YELLOW,      new Sprite{texture, {225, 193, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREEN,       new Sprite{texture, {225, 225, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_RED,	        new Sprite{texture, {225, 257, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_BROWN,       new Sprite{texture, {225, 289, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_LAVENDER,    new Sprite{texture, {257, 193, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_ORANGE,      new Sprite{texture, {257, 225, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_BLUE,        new Sprite{texture, {257, 257, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_PURPLE,      new Sprite{texture, {257, 289, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREY_IDLE,   new Sprite{texture, {161, 1, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREY_ANIM_1, new Sprite{texture, {129, 1, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GRAY_ANIM_2, new Sprite{texture, {161, 1, BRICK_WIDTH, BRICK_HEIGHT}} }
	};
}

LevelBrickLoader::~LevelBrickLoader()
{
	for (auto const&[spriteId, sprite] : sprites)
	{
		delete sprite;
	}
}

std::vector<Entity*> LevelBrickLoader::loadLevel(int levelNumber)
{
	// Let's do 11 bricks and a wall on each side for now
	static const int NUM_TILES_WIDE = 13;
	static const int NUM_TILES_HIGH = 16;

	// The tiles are square 31x31
	static const int TILE_SIZE = 31;
	static const int OFFSET = TILE_SIZE * 0.5;

	// For now we only have one level so always load that one.
	std::vector<std::vector<int>> level = levelOneBricks();

	std::vector<Entity*> entities;
	float locationX, locationY;
	int i, j;

	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			int spriteId = level[i][j];
			if (spriteId == BrickId::NONE) continue;

			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };

			Vector2 extents{ TILE_SIZE * 0.5f, BRICK_HEIGHT * 0.5f };
			int numHitsToDestroy = spriteId == 8 ? 2 : 1;
			int scoreValue = numHitsToDestroy == 2 ? 100 : 50;
			entities.push_back(new Brick{ sprites[spriteId], AABB{ position, extents }, position, numHitsToDestroy, scoreValue });
		}
	}

	return entities;
}