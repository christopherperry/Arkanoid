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

enum BrickId
{
	NONE,

	// Bricks
	BRICK_GOLD,
	BRICK_GREEN,
	BRICK_RED,
	BRICK_BROWN,
	BRICK_PINK,
	BRICK_ORANGE,
	BRICK_BLUE,
	BRICK_PURPLE,
	BRICK_GREY_IDLE,
	BRICK_GREY_ANIM_1,
	BRICK_GREY_ANIM_2,

};

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
		{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 4, 2, 7, 0, 0, 0, 0, 0, 0, 0 },
		{ 5, 4, 2, 7, 3, 0, 0, 0, 0, 0, 0 },
		{ 5, 4, 2, 7, 3, 5, 0, 0, 0, 0, 0 },
		{ 5, 4, 2, 7, 3, 5, 4, 0, 0, 0, 0 },
		{ 5, 4, 2, 7, 3, 5, 4, 2, 0, 0, 0 },
		{ 5, 4, 2, 7, 3, 5, 4, 2, 7, 0, 0 },
		{ 5, 4, 2, 7, 3, 5, 4, 2, 7, 3, 0 },
		{ 5, 4, 2, 7, 3, 5, 4, 2, 7, 3, 0 },
		{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 5 }
	};
}

std::vector<std::vector<int>> getBricksForLevel(int levelNumber)
{
	assert((levelNumber > 0) && levelNumber <= Constants::NUM_LEVELS);

	return levelTwoBricks();

	/*switch (levelNumber)
	{
	case 1:
		return levelOneBricks();
	case 2:
		return levelTwoBricks();
	}*/
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
		{BRICK_GREY_ANIM_2, new Sprite{texture, {161,   1, BRICK_WIDTH, BRICK_HEIGHT}} },
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

			int numHitsToDestroy = 1;
			if (spriteId == 1)
			{
				numHitsToDestroy = -1; // indestructable
			}
			else if (spriteId == 9)
			{
				numHitsToDestroy = 2;
			}

			int scoreValue = numHitsToDestroy == 2 ? 100 : 50;

			entities.push_back(new Brick{ sprites[spriteId], AABB{ position, extents }, position, numHitsToDestroy, scoreValue });
		}
	}

	return entities;
}