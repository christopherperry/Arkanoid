#include <vector>
#include <assert.h>
#include "LevelBrickLoader.h"
#include "../collisions/AABB.h"
#include "../entities/Entity.h"
#include "../math/Vector2.h"
#include "../entities/BackgroundTile.h"
#include "../entities/Brick.h"
#include "../entities/Wall.h"
#include "../entities/WallCollider.h"
#include "../Constants.h"

std::vector<std::vector<int>> levelZero()
{
	return std::vector<std::vector<int>>
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	};
}

std::vector<std::vector<int>> levelOneBricks()
{
	return std::vector<std::vector<int>>
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
		{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
	};
}

std::vector<std::vector<int>> levelTwoBricks()
{
	return std::vector<std::vector<int>>
	{
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 4, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 4, 8, 2, 7, 0, 0, 0, 0, 0, 0, 0 },
		{ 4, 8, 2, 7, 3, 0, 0, 0, 0, 0, 0 },
		{ 4, 8, 2, 7, 3, 4, 8, 2, 0, 0, 0 },
		{ 4, 8, 2, 7, 3, 4, 8, 2, 7, 0, 0 },
		{ 4, 8, 2, 7, 3, 4, 8, 2, 7, 3, 0 },
		{ 4, 8, 2, 7, 3, 4, 8, 2, 7, 3, 0 },
		{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4 }
	};
}

std::vector<std::vector<int>> levelThreeBricks()
{
	return std::vector<std::vector<int>>
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 11, 11, 11 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 7, 7, 7, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7 }
	};
}

std::vector<std::vector<int>> levelFourBricks()
{
	return std::vector<std::vector<int>>
	{
		{ 0,   0, 0, 0, 0,   0,   0, 0, 0, 0,   0 },
		{ 0,   0, 0, 0, 0,   0,   0, 0, 0, 0,   0 },

		{ 0,   9, 6, 2, 5,   0,   6, 2, 7, 9,   0 },
		{ 0,   7, 2, 6, 3,   0,   2, 6, 9, 7,   0 },
		{ 0,   2, 5, 3, 6,   0,   7, 9, 6, 2,   0 },
		{ 0,   6, 3, 5, 2,   0,   9, 7, 2, 6,   0 },
		{ 0,   3, 6, 2, 7,   0,   6, 2, 5, 3,   0 },
		{ 0,   5, 2, 6, 9,   0,   2, 6, 3, 5,   0 },
		{ 0,   2, 7, 9, 6,   0,   5, 3, 6, 2,   0 },
		{ 0,   6, 9, 7, 2,   0,   3, 5, 2, 6,   0 },
		{ 0,   9, 6, 2, 5,   0,   6, 2, 7, 9,   0 },
		{ 0,   7, 2, 6, 3,   0,   2, 6, 9, 7,   0 },
		{ 0,   2, 5, 3, 6,   0,   7, 9, 6, 2,   0 },
		{ 0,   6, 3, 5, 2,   0,   9, 7, 2, 6,   0 },
		{ 0,   3, 6, 2, 7,   0,   6, 2, 5, 3,   0 },
		{ 0,   5, 2, 6, 9,   0,   2, 6, 3, 5,   0 },
	};
}

std::vector<std::vector<int>> levelFiveBricks()
{
	return std::vector<std::vector<int>>
	{
		{ 0,   0, 0, 6, 0, 0, 0, 6, 0, 0,   0 },
		{ 0,   0, 0, 0, 6, 0, 6, 0, 0, 0,   0 },
		{ 0,   0, 0, 0, 6, 0, 6, 0, 0, 0,   0 },
		{ 0,   0, 0, 9, 9, 9, 9, 9, 0, 0,   0 },
		{ 0,   0, 0, 9, 9, 9, 9, 9, 0, 0,   0 },
		{ 0,   0, 9, 9, 3, 9, 3, 9, 9, 0,   0 },
		{ 0,   0, 9, 9, 3, 9, 3, 9, 9, 0,   0 },
		{ 0,   9, 9, 9, 9, 9, 9, 9, 9, 9,   0 },
		{ 0,   9, 9, 9, 9, 9, 9, 9, 9, 9,   0 },
		{ 0,   9, 0, 9, 9, 9, 9, 9, 0, 9,   0 },
		{ 0,   9, 0, 9, 0, 0, 0, 9, 0, 9,   0 },
		{ 0,   9, 0, 9, 0, 0, 0, 9, 0, 9,   0 },
		{ 0,   0, 0, 0, 9, 0, 9, 0, 0, 0,   0 },
		{ 0,   0, 0, 0, 9, 0, 9, 0, 0, 0,   0 },
		{ 0,   0, 0, 0, 0, 0, 0, 0, 0, 0,   0 },
	};
}

enum BrickId
{
	NONE,

	// Unbreakable - 0pts
	BRICK_GOLD,

	// 80 pts
	BRICK_GREEN,

	// 90 pts
	BRICK_RED,

	// 60 pts
	BRICK_BROWN,

	// 110 pts
	BRICK_PINK,

	// 120 pts
	BRICK_ORANGE,

	// 100 pts
	BRICK_BLUE,

	// 70 pts
	BRICK_PURPLE, // replacement for light blue

	// 50 x Level Number pts
	BRICK_GREY_IDLE,
	BRICK_GREY_ANIM_1,

	// 50 pts
	WHITE,

};

int pointsForBrick(int brickId, int levelNumber)
{
	switch (brickId)
	{
	case BRICK_GREEN: return 80;
	case BRICK_RED: return 90;
	case BRICK_BROWN: return 60;
	case BRICK_PINK: return 110;
	case BRICK_ORANGE: return 120;
	case BRICK_BLUE: return 100;
	case BRICK_PURPLE: return 70;
	case WHITE: return 50;
	case BRICK_GREY_IDLE: return 50 * levelNumber;
	}

	return 0;
}

int hitsToDestroyBrick(int brickId, int levelNumber)
{
	switch (brickId)
	{
		case BRICK_GOLD: return -1;
		case BRICK_GREY_IDLE:
		{
			if (levelNumber < 9)
			{
				return 2;
			}

			if (levelNumber < 17)
			{
				return 3;
			}

			if (levelNumber < 25)
			{
				return 4;
			}

			return 5;
		}
		default: return 1;
	}
}

std::vector<std::vector<int>> getBricksForLevel(int levelNumber)
{
	//return levelFiveBricks();
	assert((levelNumber > 0) && levelNumber <= Constants::NUM_LEVELS);

	switch (levelNumber)
	{
	case 1:
		return levelOneBricks();
	case 2:
		return levelTwoBricks();
	case 3:
		return levelThreeBricks();
	case 4:
		return levelFourBricks();
	case 5:
		return levelFiveBricks();
	}

	return levelZero();
}

LevelBrickLoader::LevelBrickLoader(SDL_Texture* texture)
{
	// We create all of the sprites once and use them to render the level
	// we are asked to render.

	sprites = {
		// Bricks
		{BRICK_GOLD,        new Sprite{texture, {225, 193, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREEN,       new Sprite{texture, {225, 225, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_RED,	        new Sprite{texture, {225, 257, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_BROWN,       new Sprite{texture, {225, 289, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_PINK,		new Sprite{texture, {257, 193, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_ORANGE,      new Sprite{texture, {257, 225, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_BLUE,        new Sprite{texture, {257, 257, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_PURPLE,      new Sprite{texture, {257, 289, BRICK_WIDTH, BRICK_HEIGHT}} },
		{WHITE,             new Sprite{texture, {161,   1, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREY_ANIM_1, new Sprite{texture, {129,   1, BRICK_WIDTH, BRICK_HEIGHT}} },
		{BRICK_GREY_IDLE,   new Sprite{texture, {97,    1, BRICK_WIDTH, BRICK_HEIGHT}} }
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
	// For now we only have one level so always load that one.
	std::vector<std::vector<int>> bricks = getBricksForLevel(levelNumber);

	// Account for the level walls and roof
	float xOffset = Constants::TILE_SIZE + Constants::OFFSET;
	float yOffset = Constants::TILE_SIZE + Constants::OFFSET;

	std::vector<Entity*> entities;
	float locationX, locationY;

	for (int i = 0; i < bricks.size(); i++)
	{
		locationY = (i * Constants::BRICK_HEIGHT) + yOffset;

		for (int j = 0; j < Constants::NUM_BRICKS_WIDE; j++)
		{
			int spriteId = bricks[i][j];
			if (spriteId == BrickId::NONE) continue;

			locationX = (j * Constants::BRICK_WIDTH) + xOffset;
			Vector2 position{ locationX, locationY };

			Vector2 extents{ Constants::BRICK_WIDTH * 0.5f, Constants::BRICK_HEIGHT * 0.5f };

			int numHitsToDestroy = hitsToDestroyBrick(spriteId, levelNumber);
			int scoreValue = pointsForBrick(spriteId, levelNumber);
			std::string tag = ((spriteId == BrickId::BRICK_GOLD) || (spriteId == BrickId::BRICK_GREY_IDLE)) ? "unbreakable-brick" : "brick" ;

			entities.push_back(new Brick{ sprites[spriteId], AABB{ position, extents }, position, numHitsToDestroy, scoreValue, tag});
		}
	}

	return entities;
}