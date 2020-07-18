#include <map>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "sprites/sprite.h"

Game::Game(SDL_Texture* texture)
{
	sprites = {
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
		{BACKGROUND_BLUE, Sprite{texture, {129, 385, 31, 31}} }
	};

	int wallsAndBricks[16][13] =
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

	int locationX, locationY;
	int i, j;

	// The Background Tiles
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = i * TILE_SIZE;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			locationX = j * TILE_SIZE;
			SDL_Point position{ locationX, locationY };
			BoundingBox boundingBox{};
			entities.push_back(Entity{ getSprite(SpriteId::BACKGROUND_BLUE), boundingBox, position });
		}
	}

	// The Walls and Bricks
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = i * TILE_SIZE;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			locationX = j * TILE_SIZE;
			SDL_Point position{ locationX, locationY };

			int spriteId = wallsAndBricks[i][j];
			if (spriteId == SpriteId::NONE) continue;

			SDL_Rect box;

			// Bricks
			if (spriteId >= 0 && spriteId <= 10)
			{
				box.w = TILE_SIZE;
				box.h = BRICK_HEIGHT;
				box.x = locationX;
				box.y = locationY;
			}
			else if (spriteId >= 17 && spriteId <= 22)
			{
				box.w = TILE_SIZE;
				box.h = WALL_TOP_THICKNESS;
				box.x = locationX;
				box.y = locationY;
			}
			else
			{
				box.w = TILE_SIZE;
				box.h = TILE_SIZE;
				box.x = locationX;
				box.y = locationY;
			}

			BoundingBox boundingBox{ box };
			entities.push_back(Entity{ getSprite(spriteId), boundingBox, position });
		}
	}
}

Sprite* Game::getSprite(int id)
{
	if (id == SpriteId::NONE) return nullptr;
	return &sprites[id];
}

void Game::render(SDL_Renderer* renderer)
{
	for (Entity entity : entities)
		entity.render(renderer);
}
