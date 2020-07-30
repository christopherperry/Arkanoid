#include <map>
#include <vector>
#include <algorithm>
#include "Constants.h"
#include "Game.h"
#include "sprites/sprite.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "entities/Ball.h"
#include "Sounds.h"
#include "Text.h"
#include "TextRenderer.h"
#include "utils/logger.h"

bool isAlive(Entity* entity)
{
	return entity->isAlive();
}

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

	Vector2 bottomPosition(Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f + Constants::OFFSET, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE - 2 * Constants::OFFSET);
	Vector2 bottomExtents(Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f, Constants::TILE_SIZE * 0.5f);
	ballLossArea = new BallLossArea(AABB{ bottomPosition, bottomExtents }, bottomPosition);

	loadLevel(level);
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

void Game::loadLevel(int levelNumber)
{
	Logger::log(std::string{ "Loading level" } += std::to_string(levelNumber));

	entities::deleteAll(nonColliders);
	entities::deleteAll(wallColliders);
	entities::deleteAll(powerUps);
	entities::deleteAll(bullets);
	entities::deleteAll(bricks);

	nonColliders = levelLoader->loadNonColliders(levelNumber);
	wallColliders = levelLoader->loadWallColliders(levelNumber);
	bricks = levelLoader->loadBricks(levelNumber);

	player->reset();
}

void Game::onEvent(SDL_Event e)
{
	bool enterPressed = false;
	bool spacePressed = false;

	if (e.type == SDL_KEYDOWN)
	{
		SDL_Keycode keycode = e.key.keysym.sym;
		switch (keycode)
		{
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			{
				Logger::log("Enter Pressed");
				enterPressed = true;
				break;
			}
			case SDLK_SPACE:
			{
				Logger::log("Space Pressed");
				spacePressed = true;
				break;
			}
		}
	}

	if (enterPressed && gameState == GameState::GAME_START)
	{
		gameState = GameState::BALL_LAUNCH;
		Sounds::play(gameStart);
	}

	if (spacePressed)
	{
		if (gameState == GameState::BALL_LAUNCH)
		{
			ball->launch();
			gameState = GameState::PLAYING;
		}
		else if (gameState == GameState::PLAYING)
		{
			if (player->getState() == PlayerState::GUNNER && bulletSpawner->canSpawn())
			{
				std::pair<Bullet*, Bullet*> bulletPair = bulletSpawner->spawn(player->getPosition());
				bullets.push_back(bulletPair.first);
				bullets.push_back(bulletPair.second);
				Sounds::play(gunshot);
			}
		}
	}

	if ((gameState == GameState::PLAYING) || (gameState == GameState::BALL_LAUNCH))
	{
		player->onEvent(e);
	}
}

// TODO: do this in a faster way, i.e. don't copy just remove in place
void Game::update(float deltaTime)
{
	// Don't update positions during round win transition
	if (gameState == GameState::ROUND_WIN)
	{
		Logger::log("Round win!");
		if (level == Constants::NUM_LEVELS)
		{
			gameState = GameState::GAME_WIN;
		}
		else // Go to next level
		{
			level++;
			loadLevel(level);
			gameState = GameState::BALL_LAUNCH;
		}
		return;
	}

	if (gameState == GameState::BALL_LOSS)
	{
		if (player->isReadyToLaunch())
		{
			player->reset();
			gameState = GameState::BALL_LAUNCH;
			return;
		}
	}

	/////////////////////////////
	// BRICKS
	/////////////////////////////
	entities::Func1<Entity*> increaseScoreAndSpawnPowerUp = [&](Entity* e) {
		increaseScore(e->getScoreValue());
		PowerUpCapsule* puc = powerUpSpawner->spawn(texture,e->getPosition());
		if (puc != nullptr) powerUps.push_back(puc);
	};
	entities::removeDeadThenForEach(bricks, increaseScoreAndSpawnPowerUp);
	entities::updateEach(bricks, deltaTime);

	/////////////////////////////
	// POWER UPS
	/////////////////////////////
	entities::Func1<Entity*> collectPoints = [&](Entity* e) { increaseScore(Constants::CAPSULE_COLLECTION_POINTS); };
	entities::removeDeadThenForEach(powerUps, collectPoints);
	entities::updateEach(powerUps, deltaTime);

	// Bullets
	entities::removeDead(bullets);
	entities::updateEach(bullets, deltaTime);

	/////////////////////////////
	// PLAYER
	/////////////////////////////
	player->update(deltaTime);

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

	if (bricks.size() == 0)
	{
		gameState = GameState::ROUND_WIN;
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
	entities::checkAndNotifyCollisions(wallColliders, player);

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
		entities::checkAndNotifyCollisions(wallColliders, ball);

		// Ball vs. Bricks
		entities::Func onBallHitBrick = [&]() -> void { ball->increaseSpeed(); };
		entities::checkAndNotifyCollisions(bricks, ball, &onBallHitBrick);
	}

	// PowerUps vs Player
	entities::Func1<Entity*> onPowerUpHitPlayer = [&](Entity* capsule) -> void { 
		score += Constants::CAPSULE_COLLECTION_POINTS;
		std::string tag = capsule->tag();
		if (tag == "expand")
			player->setState(PlayerState::EXPANDED);
		if (tag == "gun")
			player->setState(PlayerState::GUNNER);
		if (tag == "shrink")
			player->setState(PlayerState::SHRUNK);
	};
	entities::checkCollidesWithAndNotify(powerUps, player, &onPowerUpHitPlayer);

	// Bullets vs Bricks
	entities::checkCollidesWithAndEmptyNotify(bullets, bricks);
}

void Game::render()
{
	switch (gameState)
	{
	case GameState::BALL_LAUNCH:
	case GameState::PLAYING:
	case GameState::BALL_LOSS:
	{
		renderGameplay();
		break;
	}
	case GameState::GAME_START:
	{
		renderGameStart();
		break;
	}
	case GameState::GAME_OVER:
	{
		renderGameOver();
		break;
	}
	}
}

void Game::renderGameStart()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	startPanel->render(renderer);
}

void Game::renderGameOver()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	gameOverPanel->render(renderer);
}

void Game::renderGameplay()
{
	entities::renderAll(nonColliders, renderer);
	entities::renderAll(bricks, renderer);
	entities::renderAll(powerUps, renderer);
	entities::renderAll(bullets, renderer);

	player->render(renderer);
	ball->render(renderer);
	scoresPanel->render(renderer, numLives, score, level);
}

void Game::increaseScore(int amount)
{
	score += amount;
	oneUpScoreCounter += amount;
	if (oneUpScoreCounter >= Constants::ONE_UP_HIGH_SCORE)
	{
		// TODO: play a sound
		numLives++;
		oneUpScoreCounter %= Constants::ONE_UP_HIGH_SCORE;
	}
}

void Game::onBallLoss()
{
	// Check number of lives. If none left signal game over.
	// If lives left reset player and ball.
	numLives--;

	entities::deleteAll(powerUps);
	entities::deleteAll(bullets);

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
		Sounds::play(ballLoss);
	}
}

void Game::onGameEnd()
{
	numLives = Constants::START_LIVES;
	score = 0;
	level = 1;
	Sounds::play(gameEnd);
}