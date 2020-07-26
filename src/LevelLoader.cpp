#include <vector>
#include "LevelLoader.h"
#include "AABB.h"
#include "Entity.h"
#include "Vector2.h"
#include "BackgroundTile.h"
#include "Brick.h"
#include "Wall.h"
#include "WallCollider.h"
#include "BallLossArea.h"

// The tiles are square 31x31
static const int TILE_SIZE = 31;
static const int OFFSET = TILE_SIZE * 0.5;
static const int BRICK_HEIGHT = 16;
static const int WALL_TOP_THICKNESS = 13;

// Let's do 11 bricks and a wall on each side for now
static const int NUM_TILES_WIDE = 13;
static const int NUM_TILES_HIGH = 16;

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

std::vector<std::vector<int>> levelOne()
{
	std::vector<std::vector<int>> levelOne =
	{
		{11, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 12},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15},
		{13,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 15},
		{13,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15},
		{13,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 15},
		{13,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 15},
		{13,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15},
		{13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15}
	};

	return levelOne;
}

LevelLoader::LevelLoader(SDL_Texture* texture)
{
	// We create all of the sprites once and use them to render the level
	// we are asked to render.

	sprites = {
		// Bricks
		{BRICK_YELLOW, new Sprite{texture, {225, 193, 31, 16}} },
		{BRICK_GREEN, new Sprite{texture, {225, 225, 31, 16}} },
		{BRICK_RED, new Sprite{texture, {225, 257, 31, 16}} },
		{BRICK_BROWN, new Sprite{texture, {225, 289, 31, 16}} },
		{BRICK_LAVENDER, new Sprite{texture, {257, 193, 31, 16}} },
		{BRICK_ORANGE, new Sprite{texture, {257, 225, 31, 16}} },
		{BRICK_BLUE, new Sprite{texture, {257, 257, 31, 16}} },
		{BRICK_PURPLE, new Sprite{texture, {257, 289, 31, 16}} },
		{BRICK_GREY_IDLE, new Sprite{texture, {161, 1, 31, 16}} },
		{BRICK_GREY_ANIM_1, new Sprite{texture, {129, 1, 31, 16}} },
		{BRICK_GRAY_ANIM_2, new Sprite{texture, {161, 1, 31, 16}} },

		// Walls
		{WALL_CORNER_TOP_LEFT, new Sprite{texture, {129, 193, 31, 31}} },
		{WALL_CORNER_TOP_RIGHT, new Sprite{texture, {193, 193, 31, 31}} },
		{WALL_LEFT_STRAIGHT, new Sprite{texture, {129, 257, 31, 31}} },
		{WALL_LEFT_RIVETED, new Sprite{texture, {129, 225, 31, 31}} },
		{WALL_RIGHT_STRAIGHT, new Sprite{texture, {193, 257, 31, 31}} },
		{WALL_RIGHT_RIVETED, new Sprite{texture, {193, 225, 31, 31}} },
		{WALL_TOP_PLAIN, new Sprite{texture, {193, 289, 31, 31}} },
		{WALL_TOP_RIVETED, new Sprite{texture, {129, 289, 31, 31}} },

		// Wall top emiter 
		{WALL_TOP_EMITER_IDLE, new Sprite{texture, {161, 289, 31, 31}} },
		{WALL_TOP_EMITER_ANIM_1, new Sprite{texture, {161, 257, 31, 31}} },
		{WALL_TOP_EMITER_ANIM_2, new Sprite{texture, {161, 225, 31, 31}} },
		{WALL_TOP_EMITER_OPEN, new Sprite{texture, {161, 193, 31, 31}} },

		// Background
		{BACKGROUND_BLUE, new Sprite{texture, {129, 385, 31, 31}} }
	};
}

LevelLoader::~LevelLoader()
{
	for (auto const&[spriteId, sprite] : sprites)
	{
		delete sprite;
	}
}

std::vector<Entity*> LevelLoader::loadLevel(int levelNumber)
{
	// For now we only have one level so always load that one.
	std::vector<std::vector<int>> level = levelOne();

	std::vector<Entity*> entities;
	float locationX, locationY;
	int i, j;

	// The Background Tiles
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (j = 1; j < NUM_TILES_WIDE - 1; j++)
		{
			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };
			AABB boundingBox{ position, {TILE_SIZE * 0.5f, TILE_SIZE * 0.5f} };
			entities.push_back(new BackgroundTile{ sprites[SpriteId::BACKGROUND_BLUE], boundingBox, position });
		}
	}

	// The Walls and Bricks
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			int spriteId = level[i][j];
			if (spriteId == SpriteId::NONE) continue;

			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };

			// Bricks
			if (spriteId >= 0 && spriteId <= 10)
			{
				Vector2 extents{ TILE_SIZE * 0.5f, BRICK_HEIGHT * 0.5f };
				int numHitsToDestroy = spriteId == 8 ? 2 : 1;
				int scoreValue = numHitsToDestroy == 2 ? 100 : 50;
				entities.push_back(new Brick{ sprites[spriteId], AABB{ position, extents }, position, numHitsToDestroy, scoreValue });
			}
			else // Wall
			{
				entities.push_back(new Wall{ sprites[spriteId], position });
			}
		}
	}

	// Create separate Entities for the walls because having boxes for each tile causes collision issues
	Vector2 leftPosition(TILE_SIZE * 0.5f, NUM_TILES_HIGH * TILE_SIZE * 0.5f);
	Vector2 leftExtents(TILE_SIZE * 0.5f, NUM_TILES_HIGH * TILE_SIZE * 0.5f);
	WallCollider* leftWall = new WallCollider(AABB{ leftPosition, leftExtents }, leftPosition);

	Vector2 rightPosition(NUM_TILES_WIDE * TILE_SIZE - TILE_SIZE * 0.5f, NUM_TILES_HIGH * TILE_SIZE * 0.5f);
	Vector2 rightExtents(TILE_SIZE * 0.5f, NUM_TILES_HIGH * TILE_SIZE * 0.5f);
	WallCollider* rightWall = new WallCollider(AABB{ rightPosition, rightExtents }, rightPosition);

	Vector2 topPosition(NUM_TILES_WIDE * TILE_SIZE * 0.5f + OFFSET, 0.0f);
	Vector2 topExtents(NUM_TILES_WIDE * TILE_SIZE * 0.5f, TILE_SIZE * 0.5f);
	WallCollider* topWall = new WallCollider(AABB{ topPosition, topExtents }, topPosition);

	entities.push_back(leftWall);
	entities.push_back(rightWall);
	entities.push_back(topWall);

	return entities;
}