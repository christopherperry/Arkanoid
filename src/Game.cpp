#include <map>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "Brick.h"
#include "sprites/sprite.h"
#include "Player.h"
#include "Ball.h"
#include "BackgroundTile.h"
#include "WallCollider.h"
#include "Wall.h"
#include "logger.h"

const static float BALL_SPEED = 300.0f / 1000.0f; // pixels per second, time is in milliseconds
const static bool RENDER_COLLIDERS = false;

Game::Game(SDL_Renderer* renderer, SDL_Texture* texture) : renderer{ renderer }, texture{ texture }
{
	paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	brickHit = Mix_LoadWAV("res/brick-hit.wav");
}

Game::~Game()
{
	Mix_FreeChunk(paddleHit);
	Mix_FreeChunk(brickHit);

	delete player;
	delete ball;
}

void Game::loadLevel()
{
	// Clean out any previously created Entities
	for (Entity* e : entities)
	{
		delete e;
	}
	entities.clear();

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
		{13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 15}
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
				int numHitsToDestroy = spriteId == 8 ? 2 : 1;
				entities.push_back(new Brick{ getSprite(spriteId), AABB{ position, extents }, position, numHitsToDestroy });
			}
			else // Wall
			{
				entities.push_back(new Wall{ getSprite(spriteId), position });
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

	if (player != nullptr)
	{
		delete player;
	}
	player = createPlayer();

	if (ball != nullptr)
	{
		delete ball;
	}
	ball = createBall();
}

void Game::onEvent(SDL_Event e)
{
	player->onEvent(e);
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

Ball* Game::createBall()
{
	float ballSize = 6;
	Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
	Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - ballSize };
	Vector2 ballExtents{ ballSize  * 0.5f, ballSize  * 0.5f };

	// Pick a random start velocity between 25 and 155 degrees
	float pi = 2 * std::acos(0);
	int randomAngle = 25 + (std::rand() % (155 - 25 + 1));
	int randomAngleRadians = randomAngle * (pi / 180.0f);
	Vector2 startVelocity = Vector2(std::cos(randomAngleRadians), -std::sin(randomAngleRadians)) * BALL_SPEED;

	return new Ball(
		getSprite(SpriteId::BALL),
		AABB{ ballPosition, ballExtents },
		ballPosition,
		startVelocity,
		brickHit,
		paddleHit
	);
}

void Game::render()
{
	for (Entity* entity : entities)
	{
		entity->render(renderer);

		if (RENDER_COLLIDERS)
		{
			entity->renderColliders(renderer);
		}
	}

	player->render(renderer);
	ball->render(renderer);

	if (RENDER_COLLIDERS)
	{
		player->renderColliders(renderer);
		ball->renderColliders(renderer);
	}
}

// TODO: do this in a faster way, i.e. don't copy just remove in place
void Game::update(float deltaTime)
{
	// Remove dead entities
	std::vector<Entity*> aliveEntities;
	for (Entity* entity : entities)
	{
		if (entity->isAlive())
		{
			aliveEntities.push_back(entity);
		}
		else
		{
			Logger::log("DELETE DEAD ENTITY!");
			delete entity;
		}
	}

	entities.clear();
	entities = aliveEntities;

	// Update our player and ball
	player->update(deltaTime);
	ball->update(deltaTime);
}

void Game::checkCollisions()
{
	// Check for player collisions
	std::vector<std::pair<Entity*, Hit*>> playerCollisions = checkCollisions(player);
	if (playerCollisions.size() > 0)
	{
		player->onCollision(playerCollisions.at(0).second);
	}

	// Check for ball collisions
	std::vector<std::pair<Entity*, Hit*>> ballCollisions = checkCollisions(ball);
	Hit* hitPlayer = ball->checkCollision(*player);
	if (hitPlayer != nullptr)
	{
		ball->onCollision(hitPlayer);
	}
	else
	{
		// Handle collisions
		for (std::pair<Entity*, Hit*>& collision : ballCollisions)
		{
			Entity* theThingWeHit = collision.first;
			theThingWeHit->onCollision(collision.second); // Passing this may be interpreted wrong if we decide to interpret it
			ball->onCollision(collision.second);

			if (RENDER_COLLIDERS)
			{
				theThingWeHit->renderCollidersHit(renderer);
			}
		}
	}
}

std::vector<std::pair<Entity*, Hit*>> Game::checkCollisions(Entity* const entity)
{
	std::vector<std::pair<Entity*, Hit*>> collisions;
	for (Entity* e : entities)
	{
		Hit* hit = entity->checkCollision(*e);
		if (hit != nullptr)
		{
			collisions.push_back(std::pair(e, hit));
		}
	}

	return collisions;
}
