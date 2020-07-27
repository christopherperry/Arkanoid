#include <map>
#include <vector>
#include <SDL_ttf.h>
#include "Game.h"
#include "sprites/sprite.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "entities/Ball.h"
#include "Text.h"
#include "TextRenderer.h"
#include "utils/logger.h"

const static bool RENDER_COLLIDERS = false;
const static float BALL_SPEED = 300.0f / 1000.0f; // pixels per second, time is in milliseconds
const static float BALL_SIZE = 6.0f;

Game::Game(float windowWidth, float windowHeight, SDL_Renderer* renderer, SDL_Texture* texture) :
	windowWidth{ windowWidth }, windowHeight{ windowHeight }, renderer{ renderer }, texture{ texture }
{
	paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	brickHit = Mix_LoadWAV("res/brick-hit.wav");
	ballLoss = Mix_LoadWAV("res/ball-loss.wav");
	gameStart = Mix_LoadMUS("res/game-start.wav");
	gameEnd = Mix_LoadMUS("res/game-end.wav");

	font = TTF_OpenFont("res/font-retro.ttf", 28);

	startPanel = new GameStartPanel(renderer, font, SDL_Rect{ 0, 0, NUM_TILES_WIDE * TILE_SIZE, NUM_TILES_HIGH * TILE_SIZE });
	gameOverPanel = new GameOverPanel(renderer, font, SDL_Rect{ 0, 0, NUM_TILES_WIDE * TILE_SIZE, NUM_TILES_HIGH * TILE_SIZE });
	scoresPanel = new ScoresPanel(renderer, font, Vector2((NUM_TILES_WIDE * TILE_SIZE) + OFFSET, 0));
	levelLoader = new LevelLoader(texture);

	player = createPlayer();
	ball = createBall();

	entities = levelLoader->loadLevel(1);

	Vector2 bottomPosition(NUM_TILES_WIDE * TILE_SIZE * 0.5f + OFFSET, NUM_TILES_HIGH * TILE_SIZE - 2 * OFFSET);
	Vector2 bottomExtents(NUM_TILES_WIDE * TILE_SIZE * 0.5f, TILE_SIZE * 0.5f);
	ballLossArea = new BallLossArea(AABB{ bottomPosition, bottomExtents }, bottomPosition);
}

Game::~Game()
{
	Mix_FreeChunk(paddleHit);
	Mix_FreeChunk(brickHit);
	Mix_FreeChunk(ballLoss);
	Mix_FreeMusic(gameStart);
	Mix_FreeMusic(gameEnd);

	delete player;
	delete ball;
	delete scoresPanel;
	delete ballLossArea;
}

void Game::playSound(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}

void Game::playMusic(Mix_Music* music)
{
	Mix_PlayMusic(music, 0);
}

void Game::onGameStart()
{
	playMusic(gameStart);
}

void Game::onGameEnd()
{
	numLives = START_LIVES;
	score = 0;
	playMusic(gameEnd);
}

void Game::reloadLevel()
{
	for (Entity* e : entities)
	{
		delete e;
	}
	entities.clear();

	entities = levelLoader->loadLevel(1);
}

void Game::onEvent(SDL_Event e)
{
	if ( (gameState == GameState::PLAYING) || (gameState == GameState::BALL_LAUNCH) )
	{
		player->onEvent(e);
	}

	switch (e.type) {
	case SDL_KEYDOWN:
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
		{
			if (gameState == GameState::GAME_START)
			{
				gameState = GameState::BALL_LAUNCH;
				onGameStart();
			}

			break;
		}
		case SDLK_SPACE:
		{
			if (gameState == GameState::BALL_LAUNCH)
			{
				ball->launch();
				gameState = GameState::PLAYING;
			}

			if (gameState == GameState::GAME_OVER)
			{
				gameState = GameState::BALL_LAUNCH;
				reloadLevel();
			}

			break;
		}
		}
	}
	}
}

Player* Game::createPlayer()
{
	int positionX = (NUM_TILES_WIDE * TILE_SIZE * 0.5f);
	int positionY = (NUM_TILES_HIGH - 2) * TILE_SIZE;
	Vector2 position = Vector2(positionX, positionY);

	return new Player(texture, position);
}

Ball* Game::createBall()
{
	Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
	Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - BALL_SIZE };
	Vector2 ballExtents{ BALL_SIZE  * 0.5f, BALL_SIZE  * 0.5f };

	return new Ball(
		new Sprite{ texture, {463, 142, 6, 6} },
		AABB{ ballPosition, ballExtents },
		ballPosition,
		brickHit,
		paddleHit
	);
}

void Game::render()
{
	if (gameState == GameState::GAME_START)
	{
		renderGameStart();
	}
	else if ((gameState == GameState::BALL_LAUNCH) || (gameState == GameState::PLAYING) || (gameState == GameState::BALL_LOSS))
	{
		renderGameplay();
	}
	else if (gameState == GameState::GAME_OVER)
	{
		renderGameOver();
	}
}

void Game::renderGameStart()
{
	Logger::log("Render Game Start");
	for (Entity* entity : entities)
	{
		if (entity->tag() != "brick")
		{
			entity->render(renderer);
		}
	}

	scoresPanel->render(renderer, numLives, score, level);
	startPanel->render(renderer);
}

void Game::renderGameOver()
{
	Logger::log("Render Game Over");
	for (Entity* entity : entities)
	{
		if (entity->tag() != "brick")
		{
			entity->render(renderer);
		}
	}

	scoresPanel->render(renderer, numLives, score, level);
	gameOverPanel->render(renderer);
}

void Game::renderGameplay()
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
	scoresPanel->render(renderer, numLives, score, level);

	if (RENDER_COLLIDERS)
	{
		player->renderColliders(renderer);
		ball->renderColliders(renderer);
		ballLossArea->renderColliders(renderer);
	}
}

void Game::onBallLoss()
{
	// Check number of lives. If none left signal game over.
	// If lives left reset player and ball.
	numLives--;

	gameState = GameState::BALL_LOSS;
	player->dissolve();

	if (numLives <= 0)
	{
		numLives = 0;
		gameState = GameState::GAME_OVER;
		onGameEnd();
	}
	else
	{
		playSound(ballLoss);
	}
}

// TODO: do this in a faster way, i.e. don't copy just remove in place
void Game::update(float deltaTime)
{
	/////////////////////////////
	// WORLD
	/////////////////////////////
	std::vector<Entity*> aliveEntities;
	for (Entity* entity : entities)
	{
		if (entity->isAlive())
		{
			aliveEntities.push_back(entity);
		}
		else
		{
			score += entity->getScoreValue();
			delete entity;
		}
	}
	entities.clear();
	entities = aliveEntities;

	/////////////////////////////
	// PLAYER
	/////////////////////////////
	player->update(deltaTime);

	if (gameState == GameState::BALL_LOSS)
	{
		if (player->isReadyToLaunch())
		{
			gameState == GameState::BALL_LAUNCH;
		}
	}

	/////////////////////////////
	// BALL
	/////////////////////////////
	// Make the ball "stick" to the paddle on pre-launch
	if (gameState == GameState::BALL_LAUNCH)
	{
		Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
		Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - BALL_SIZE };
		ball->reset(ballPosition);
	}
	else
	{
		ball->update(deltaTime);
	}
}

void Game::checkCollisions()
{
	if (gameState != GameState::PLAYING && gameState != GameState::BALL_LAUNCH)
	{
		return;
	}

	if (ballLossArea->collidesWith(*ball))
	{
		onBallLoss();
		return;
	}

	// Player vs. Level
	std::vector<std::pair<Entity*, Hit*>> playerCollisions = checkCollisions(player);
	if (playerCollisions.size() > 0)
	{
		player->onCollision(playerCollisions.at(0).second);
	}

	// Ball vs. Player
	Hit* hitPlayer = ball->checkCollision(*player);
	if (hitPlayer != nullptr)
	{
		ball->onCollision(hitPlayer);
	}
	else // Ball vs. Level
	{
		std::vector<std::pair<Entity*, Hit*>> ballCollisions = checkCollisions(ball);
		if (ballCollisions.size() > 0)
		{
			// Let's just handle one for now
			Entity* theThingWeHit = ballCollisions[0].first;
			theThingWeHit->onCollision(ballCollisions[0].second); // Passing this may be interpreted wrong if we decide to interpret it
			ball->onCollision(ballCollisions[0].second);

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
