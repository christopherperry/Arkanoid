#include <vector>
#include "LevelLoader.h"
#include "../collisions/AABB.h"
#include "../entities/Entity.h"
#include "../math/Vector2.h"
#include "../entities/BackgroundTile.h"
#include "../entities/Brick.h"
#include "../entities/Wall.h"
#include "../entities/WallCollider.h"
#include "../utils/Util.h"

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
	NONE,

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

};

std::vector<std::vector<int>> levelOne()
{
	std::vector<std::vector<int>> levelOne =
	{
		{1,  7,  8,  7,  8,  7,  8,  7,  8,  7,  8,  7, 2},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 5}
	};

	return levelOne;
}

LevelLoader::LevelLoader(SDL_Texture* texture)
{
	// We create all of the sprites once and use them to render the level
	// we are asked to render.
	sprites = {

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

	levelBrickLoader = new LevelBrickLoader(texture);
}

LevelLoader::~LevelLoader()
{
	SafeDelete(levelBrickLoader);

	for (auto const&[spriteId, sprite] : sprites)
	{
		SafeDelete(sprite);
	}
}

std::vector<Entity*> LevelLoader::loadWallColliders(int level) const
{
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

	return std::vector<Entity*>{ leftWall, rightWall, topWall };
}

std::vector<Entity*> LevelLoader::loadNonColliders(int level) const
{
	std::vector<Entity*> entities;
	float locationX, locationY;

	// The Background Tiles
	for (int i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (int j = 1; j < NUM_TILES_WIDE - 1; j++)
		{
			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };
			AABB boundingBox{ position, {TILE_SIZE * 0.5f, TILE_SIZE * 0.5f} };
			entities.push_back(new BackgroundTile{ sprites.at(SpriteId::BACKGROUND_BLUE), boundingBox, position });
		}
	}

	// For now we only have one level so always load that one.
	std::vector<std::vector<int>> theLevel = levelOne();

	// The Walls
	for (int i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (int j = 0; j < NUM_TILES_WIDE; j++)
		{
			int spriteId = theLevel[i][j];
			if (spriteId == SpriteId::NONE) continue;

			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };

			entities.push_back(new Wall(sprites.at(spriteId), position ));
		}
	}

	return entities;
}

std::vector<Entity*> LevelLoader::loadBricks(int level) const
{
	return levelBrickLoader->loadLevel(level);
}