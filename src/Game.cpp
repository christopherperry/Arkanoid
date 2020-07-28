#include <map>
#include <vector>
#include <algorithm>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Game.h"
#include "sprites/sprite.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "entities/Ball.h"
#include "Text.h"
#include "TextRenderer.h"
#include "utils/logger.h"

Game::Game(float windowWidth, float windowHeight, SDL_Renderer* renderer, SDL_Texture* texture) :
	windowWidth{ windowWidth }, windowHeight{ windowHeight }, renderer{ renderer }, texture{ texture }
{
	paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	brickHit = Mix_LoadWAV("res/brick-hit.wav");
	ballLoss = Mix_LoadWAV("res/ball-loss.wav");
	gunshot = Mix_LoadWAV("res/gunshot.wav");
	gameStart = Mix_LoadMUS("res/game-start.wav");
	gameEnd = Mix_LoadMUS("res/game-end.wav");

	font = TTF_OpenFont("res/font-retro.ttf", 28);

	startPanel = new GameStartPanel(texture, renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	gameOverPanel = new GameOverPanel(renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	scoresPanel = new ScoresPanel(renderer, font, Vector2((Constants::NUM_TILES_WIDE * Constants::TILE_SIZE) + Constants::OFFSET, 0));
	levelLoader = new LevelLoader(texture);
	bulletSpawner = new BulletSpawner(texture);

	player = Player::createNew(texture);
	ball = Ball::createNew(texture, player->getPaddleTopCenterPosition(), brickHit, paddleHit);

	nonColliders = levelLoader->loadNonColliders(1);
	wallColliders = levelLoader->loadWallColliders(1);
	bricks = levelLoader->loadBricks(1);

	Vector2 bottomPosition(Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f + Constants::OFFSET, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE - 2 * Constants::OFFSET);
	Vector2 bottomExtents(Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f, Constants::TILE_SIZE * 0.5f);
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
	delete levelLoader;
	delete bulletSpawner;
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
	numLives = Constants::START_LIVES;
	score = 0;
	playMusic(gameEnd);
}

void Game::reloadLevel()
{
	destroyEntities();
	destroyPowerUps();
	destroyBullets();

	nonColliders = levelLoader->loadNonColliders(1);
	wallColliders = levelLoader->loadWallColliders(1);
	bricks = levelLoader->loadBricks(1);
}

void Game::destroyEntities()
{
	for (Entity* e : nonColliders)
	{
		delete e;
	}
	nonColliders.clear();

	for (Entity* w : wallColliders)
	{
		delete w;
	}
	wallColliders.clear();
}

void Game::destroyBricks()
{
	for (Entity* b : bricks)
	{
		delete b;
	}
	bricks.clear();
}

void Game::destroyPowerUps()
{
	for (PowerUpCapsule* c : powerUpCapsules)
	{
		delete c;
	}
	powerUpCapsules.clear();
}

void Game::destroyBullets()
{
	for (Bullet* b : bullets)
	{
		delete b;
	}
	bullets.clear();
}

void Game::onEvent(SDL_Event e)
{
	if ((gameState == GameState::PLAYING) || (gameState == GameState::BALL_LAUNCH))
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

			if (player->getState() == PlayerState::GUNNER && bulletSpawner->canSpawn())
			{
				std::pair<Bullet*, Bullet*> bulletPair = bulletSpawner->spawn(player->getPosition());
				bullets.push_back(bulletPair.first);
				bullets.push_back(bulletPair.second);
				playSound(gunshot);
			}

			break;
		}
		}
	}
	}
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
	for (Entity* entity : nonColliders)
	{
		entity->render(renderer);
	}

	scoresPanel->render(renderer, numLives, score, level);
	startPanel->render(renderer);
}

void Game::renderGameOver()
{
	Logger::log("Render Game Over");
	for (Entity* entity : nonColliders)
	{
		entity->render(renderer);
	}

	scoresPanel->render(renderer, numLives, score, level);
	gameOverPanel->render(renderer);
}

void Game::renderGameplay()
{
	for (Entity* entity : nonColliders)
	{
		entity->render(renderer);
	}

	for (Entity* wc : wallColliders)
	{
		if (Constants::RENDER_COLLIDERS)
		{
			wc->renderColliders(renderer);
		}
	}

	for (Entity* brick : bricks)
	{
		brick->render(renderer);

		if (Constants::RENDER_COLLIDERS)
		{
			brick->renderColliders(renderer);
		}
	}

	// Power Ups
	for (PowerUpCapsule* capsule : powerUpCapsules)
	{
		capsule->render(renderer);
	}

	// Bullets
	for (Bullet* bullet : bullets)
	{
		bullet->render(renderer);
	}

	player->render(renderer);
	ball->render(renderer);
	scoresPanel->render(renderer, numLives, score, level);

	if (Constants::RENDER_COLLIDERS)
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

	destroyPowerUps();
	destroyBullets();

	gameState = GameState::BALL_LOSS;
	player->setState(PlayerState::DISSOLVE);

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
	// BRICKS
	/////////////////////////////
	std::vector<Entity*> aliveBricks;
	for (Entity* brick : bricks)
	{
		if (brick->isAlive())
		{
			aliveBricks.push_back(brick);
		}
		else // Brick Break!
		{
			PowerUpCapsule* puc = powerUpSpawner->spawn(texture, brick->getPosition());
			if (puc != nullptr)
			{
				powerUpCapsules.push_back(puc);
			}

			score += brick->getScoreValue();
			delete brick;
		}
	}
	bricks.clear();
	bricks = aliveBricks;

	// Power Ups
	std::vector<PowerUpCapsule*> alivePowerUps;
	for (PowerUpCapsule* capsule : powerUpCapsules)
	{
		if (capsule->isAlive())
		{
			capsule->update(deltaTime);
			alivePowerUps.push_back(capsule);
		}
		else
		{
			delete capsule;
		}
	}
	powerUpCapsules.clear();
	powerUpCapsules = alivePowerUps;

	// Bullets
	std::vector<Bullet*> aliveBullets;
	for (Bullet* bullet : bullets)
	{
		if (bullet->isAlive())
		{
			bullet->update(deltaTime);
			aliveBullets.push_back(bullet);
		}
		else // Dead bullet
		{
			delete bullet;
		}
	}
	bullets.clear();
	bullets = aliveBullets;

	/////////////////////////////
	// PLAYER
	/////////////////////////////
	player->update(deltaTime);

	if (gameState == GameState::BALL_LOSS)
	{
		if (player->isReadyToLaunch())
		{
			player->reset();
			gameState = GameState::BALL_LAUNCH;
		}
	}

	/////////////////////////////
	// BALL
	/////////////////////////////
	// Make the ball "stick" to the paddle on pre-launch
	if (gameState == GameState::BALL_LAUNCH)
	{
		Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
		Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - (Constants::BALL_SIZE * 0.5f) };
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

	// Player vs. Walls
	for (Entity* wall : wallColliders)
	{
		Hit* hit = player->checkCollision(*wall);
		if (hit != nullptr)
		{
			player->onCollision(hit);
			delete hit;
		}
	}

	// Ball vs. Player
	Hit* hitPlayer = ball->checkCollision(*player);
	if (hitPlayer != nullptr)
	{
		ball->onCollision(hitPlayer);
		delete hitPlayer;
	}
	else
	{
		// Ball vs. Walls
		for (Entity* wall : wallColliders)
		{
			Hit* hit = ball->checkCollision(*wall);
			if (hit != nullptr)
			{
				ball->onCollision(hit);
				delete hit;
			}
		}

		// Ball vs. Bricks
		for (Entity* brick : bricks)
		{
			Hit* hit = ball->checkCollision(*brick);
			if (hit != nullptr)
			{
				ball->onCollision(hit);
				brick->onCollision(hit);
				delete hit;

				if (Constants::RENDER_COLLIDERS)
				{
					brick->renderCollidersHit(renderer);
				}
			}
		}
	}

	// PowerUps vs Player
	for (PowerUpCapsule* capsule : powerUpCapsules)
	{
		if (capsule->collidesWith(*player))
		{
			capsule->onCollision(nullptr);
			PowerUp powerUp = capsule->getPowerUp();
			switch (powerUp)
			{
			case PowerUp::EXPAND:
				player->setState(PlayerState::EXPANDED);
				break;
			case PowerUp::GUN:
				player->setState(PlayerState::GUNNER);
				break;
			case PowerUp::SHRINK:
				player->setState(PlayerState::SHRUNK);
				break;
			}
		}
	}

	// Bullets vs Bricks
	for (Bullet* bullet : bullets)
	{
		for (Entity* brick : bricks)
		{
			if (bullet->collidesWith(*brick))
			{
				brick->onCollision(nullptr);
				bullet->onCollision(nullptr);
			}
		}
	}
}
