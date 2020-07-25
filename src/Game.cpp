#include <map>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "Brick.h"
#include "sprites/sprite.h"
#include "Player.h"
#include "Ball.h"
#include "BackgroundTile.h"

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
		{BACKGROUND_BLUE, Sprite{texture, {129, 385, 31, 31}} },

		// Player medium
		{PLAYER_LEFT_MEDIUM, Sprite{texture, {235, 175, 21, 11}} },
		{PLAYER_RIGHT_MEDIUM, Sprite{texture, {257, 175, 21, 11}} },

		// The ball
		{BALL, Sprite{texture, {463, 142, 6, 6}} }
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

	float locationX, locationY;
	int i, j;

	// The Background Tiles
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };
			AABB boundingBox{ position, {TILE_SIZE * 0.5f, TILE_SIZE * 0.5f} };
			entities.push_back(new BackgroundTile{ getSprite(SpriteId::BACKGROUND_BLUE), boundingBox, position });
		}
	}

	// The Walls and Bricks
	for (i = 0; i < NUM_TILES_HIGH; i++)
	{
		locationY = (i * TILE_SIZE) + OFFSET;

		for (j = 0; j < NUM_TILES_WIDE; j++)
		{
			int spriteId = wallsAndBricks[i][j];
			if (spriteId == SpriteId::NONE) continue;

			locationX = (j * TILE_SIZE) + OFFSET;
			Vector2 position{ locationX, locationY };

			// Bricks
			if (spriteId >= 0 && spriteId <= 10)
			{
				Vector2 extents{ TILE_SIZE * 0.5f, BRICK_HEIGHT * 0.5f };
				entities.push_back(new Brick{ getSprite(spriteId), AABB{ position, extents }, position });
			}
			else if (spriteId >= 17 && spriteId <= 22) // Top Wall
			{
				Vector2 extents{ TILE_SIZE * 0.5f, WALL_TOP_THICKNESS * 0.5f };
				entities.push_back(new Entity{ getSprite(spriteId), AABB{ position, extents }, position });
			}
			else
			{
				Vector2 extents{ TILE_SIZE * 0.5f, TILE_SIZE * 0.5f };
				entities.push_back(new Entity{ getSprite(spriteId), AABB{ position, extents }, position });
			}
		}
	}
}

Sprite* Game::getSprite(int id)
{
	if (id == SpriteId::NONE) return nullptr;
	return &sprites[id];
}

Player* Game::createPlayer()
{
	int positionX = (NUM_TILES_WIDE * TILE_SIZE * 0.5f);
	int positionY = (NUM_TILES_HIGH - 2) * TILE_SIZE;
	Vector2 position = Vector2(positionX, positionY);

	Vector2 extents{ 21.0f, 5.5f }; // Paddle size is 42 by 11
	AABB box{ position, extents };

	return new Player(
		getSprite(SpriteId::PLAYER_LEFT_MEDIUM),
		getSprite(SpriteId::PLAYER_RIGHT_MEDIUM),
		box,
		position
	);
}

Ball* Game::createBall(Player* player)
{
	float ballSize = 6;
	Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
	Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - ballSize };
	Vector2 ballExtents{ ballSize  * 0.5f, ballSize  * 0.5f };

	return new Ball(
		getSprite(SpriteId::BALL),
		AABB{ ballPosition, ballExtents },
		ballPosition
	);
}

void Game::render(SDL_Renderer* renderer)
{
	for (Entity* entity : entities)
	{
		entity->render(renderer);
		//entity->renderColliders(renderer);
	}
}

std::vector<Entity*> Game::checkCollisions(Ball* const ball)
{
	std::vector<Entity*> collisions;
	for (Entity* entity : entities)
	{
		if (ball->collidesWith(*entity))
		{
			collisions.push_back(entity);
		}
	}

	return collisions;
}
