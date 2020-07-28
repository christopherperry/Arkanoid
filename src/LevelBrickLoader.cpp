#include <vector>
#include "LevelBrickLoader.h"
#include "collisions/AABB.h"
#include "entities/Entity.h"
#include "math/Vector2.h"
#include "entities/BackgroundTile.h"
#include "entities/Brick.h"
#include "entities/Wall.h"
#include "entities/WallCollider.h"
#include "Constants.h"

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
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
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
	// For now we only have one level so always load that one.
	std::vector<std::vector<int>> bricks = levelOneBricks();

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
			int numHitsToDestroy = spriteId == 8 ? 2 : 1;
			int scoreValue = numHitsToDestroy == 2 ? 100 : 50;

			entities.push_back(new Brick{ sprites[spriteId], AABB{ position, extents }, position, numHitsToDestroy, scoreValue });
		}
	}

	return entities;
}