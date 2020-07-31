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

Game::Game(float windowWidth, float windowHeight, SDL_Renderer* renderer, SDL_Texture* texture) :
	windowWidth{ windowWidth }, windowHeight{ windowHeight }, renderer{ renderer }, texture{ texture }
{
	shrink = Mix_LoadWAV("res/shrink.wav");
	expand = Mix_LoadWAV("res/expand.wav");
	extraLife = Mix_LoadWAV("res/extra-life.wav");
	paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	paddleHit = Mix_LoadWAV("res/paddle-hit.wav");
	brickHit = Mix_LoadWAV("res/brick-hit.wav");
	brickHitUnbreakable = Mix_LoadWAV("res/unbreakable-brick.wav");
	ballLoss = Mix_LoadWAV("res/ball-loss.wav");
	gunshot = Mix_LoadWAV("res/gunshot.wav");
	gameStart = Mix_LoadMUS("res/game-start.wav");
	gameEnd = Mix_LoadMUS("res/game-end.wav");

	font = TTF_OpenFont("res/font-retro.ttf", 28);

	startPanel = new GameStartPanel(texture, renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	roundStartPanel = new RoundStartPanel(renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	gameOverPanel = new GameOverPanel(renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	gameWinPanel = new GameWinPanel(texture, renderer, font, SDL_Rect{ 0, 0, Constants::NUM_TILES_WIDE * Constants::TILE_SIZE, Constants::NUM_TILES_HIGH * Constants::TILE_SIZE });
	scoresPanel = new ScoresPanel(renderer, font, Vector2((Constants::NUM_TILES_WIDE * Constants::TILE_SIZE) + Constants::OFFSET, 0));
	levelLoader = new LevelLoader(texture);
	bulletSpawner = new BulletSpawner(texture);

	player = Player::createNew(texture);
	ball = Ball::createNew(texture, player->getPaddleTopCenterPosition(), brickHit, brickHitUnbreakable, paddleHit);

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

/////////////////////////////////////////////////////////
// onEvent
/////////////////////////////////////////////////////////
void Game::onEvent(SDL_Event e)
{
	SDL_Keycode keycode = e.key.keysym.sym;
	switch (keycode)
	{
	case SDLK_RETURN:
	case SDLK_KP_ENTER:
	{
		Logger::log("Enter Pressed");
		enterPressed = e.type == SDL_KEYDOWN;
		break;
	}
	case SDLK_SPACE:
	{
		Logger::log("Space Pressed");
		spacePressed = e.type == SDL_KEYDOWN;
		Logger::log(std::to_string(spacePressed));
		break;
	}
	}

	if ((gameState == GameState::PLAYING) || (gameState == GameState::BALL_LAUNCH))
	{
		player->onEvent(e);
	}
}

/////////////////////////////////////////////////////////
// update
/////////////////////////////////////////////////////////
void Game::update(float deltaTime)
{
	TimerTask::removeFinished(timerTasks);
	TimerTask::update(timerTasks, deltaTime);

	switch (gameState)
	{
	case GameState::GAME_START:
		updateGameStart(deltaTime);
		break;
	case GameState::ROUND_START:
		updateRoundStart(deltaTime);
		break;
	case GameState::BALL_LAUNCH:
		updateBallLaunch(deltaTime);
		break;
	case GameState::PLAYING:
		updateGameplay(deltaTime);
		break;
	case GameState::BALL_LOSS:
		updateBallLoss(deltaTime);
		break;
	case GameState::ROUND_WIN:
		updateRoundWin(deltaTime);
		break;
	}
}

void Game::updateGameStart(float deltaTime)
{
	level = 1;
	score = 0;
	player->reset();

	if (enterPressed)
	{
		loadLevel(level);
		gameState = GameState::ROUND_START;
		Sounds::play(gameStart);

		// 2 second delay then changes the state
		timerTasks.push_back(new TimerTask(2000, [&]() { gameState = GameState::BALL_LAUNCH; }));
	}
}

void Game::updateRoundStart(float deltaTime)
{
	// Do nothing, we're waiting on the task we kicked off
	// see updateGameStart()
}

void Game::updateBallLaunch(float deltaTime)
{
	player->update(deltaTime);

	// Stick the ball to the paddle
	Vector2 centerOfPaddle = player->getPaddleTopCenterPosition();
	Vector2 ballPosition{ centerOfPaddle.x, centerOfPaddle.y - (Constants::BALL_SIZE * 0.5f) };
	ball->reset(ballPosition);

	if (spacePressed)
	{
		ball->launch();
		gameState = GameState::PLAYING;
	}
}

void Game::updateGameplay(float deltaTime)
{
	// Game Over Scenario
	if (numLives <= 0)
	{
		numLives = 0;
		gameState = GameState::GAME_OVER;
		onGameEnd();

		// We'll go back to the title screen after five seconds
		timerTasks.push_back(new TimerTask(5000, [&]() { gameState = GameState::GAME_START; }));

		// early exit
		return;
	}

	/////////////////////////////
	// BRICKS
	/////////////////////////////
	functions::Func1<Entity*> increaseScoreAndSpawnPowerUp = [&](Entity* e) {
		increaseScore(e->getScoreValue());
		PowerUpCapsule* puc = powerUpSpawner->spawn(texture, e->getPosition());
		if (puc != nullptr) powerUps.push_back(puc);
	};
	entities::removeDeadThenForEach(bricks, increaseScoreAndSpawnPowerUp);
	entities::updateEach(bricks, deltaTime);

	// Early exit on round win
	if (bricks.size() == 0)
	{
		gameState = GameState::ROUND_WIN;
		return;
	}

	/////////////////////////////
	// POWER UPS
	/////////////////////////////
	functions::Func1<Entity*> collectPoints = [&](Entity* e) { increaseScore(Constants::CAPSULE_COLLECTION_POINTS); };
	entities::removeDeadThenForEach(powerUps, collectPoints);
	entities::updateEach(powerUps, deltaTime);

	/////////////////////////////
	// BULLETS
	/////////////////////////////
	entities::removeDead(bullets);
	entities::updateEach(bullets, deltaTime);

	if (spacePressed && player->getState() == PlayerState::GUNNER && bulletSpawner->canSpawn())
	{
		std::pair<Bullet*, Bullet*> bulletPair = bulletSpawner->spawn(player->getPosition());
		bullets.push_back(bulletPair.first);
		bullets.push_back(bulletPair.second);
		Sounds::play(gunshot);
	}

	/////////////////////////////
	// PLAYER and BALL
	/////////////////////////////
	player->update(deltaTime);
	ball->update(deltaTime);
}

void Game::updateBallLoss(float deltaTime)
{
	player->update(deltaTime);
	ball->update(deltaTime);

	if (player->isReadyToLaunch())
	{
		player->reset();
		gameState = GameState::BALL_LAUNCH;
	}
}

void Game::updateRoundWin(float deltaTime)
{
	if (level == Constants::NUM_LEVELS)
	{
		gameState = GameState::GAME_WIN;

		// 10 second delay then changes the state
		timerTasks.push_back(new TimerTask(10000, [&]() { gameState = GameState::GAME_START; }));
	}
	else // Go to next round
	{
		level++;
		loadLevel(level);
		gameState = GameState::ROUND_START;

		// 2 second delay then changes the state
		timerTasks.push_back(new TimerTask(2000, [&]() { gameState = GameState::BALL_LAUNCH; }));
	}
}

/////////////////////////////////////////////////////////
// checkCollisions
/////////////////////////////////////////////////////////
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
		functions::Func onBallHitBrick = [&]() -> void { ball->increaseSpeed(); };
		entities::checkAndNotifyCollisions(bricks, ball, &onBallHitBrick);
	}

	// PowerUps vs Player
	functions::Func1<Entity*> onPowerUpHitPlayer = [&](Entity* capsule) -> void {
		score += Constants::CAPSULE_COLLECTION_POINTS;
		std::string tag = capsule->tag();
		if (tag == "expand") {
			player->setState(PlayerState::EXPANDED);
			Sounds::play(expand);
		}
		if (tag == "gun") {
			player->setState(PlayerState::GUNNER);
			Sounds::play(expand);
		}
		if (tag == "shrink") {
			player->setState(PlayerState::SHRUNK);
			Sounds::play(shrink);
		}
			
	};
	entities::checkCollidesWithAndNotify(powerUps, player, &onPowerUpHitPlayer);

	// Bullets vs Bricks
	entities::checkCollidesWithAndEmptyNotify(bullets, bricks);
}

/////////////////////////////////////////////////////////
// render
/////////////////////////////////////////////////////////
void Game::render()
{
	switch (gameState)
	{
	case GameState::GAME_START:
		renderGameStart();
		break;
	case GameState::ROUND_START:
		renderRoundStart();
		break;
	case GameState::BALL_LAUNCH:
	case GameState::PLAYING:
	case GameState::BALL_LOSS:
	case GameState::ROUND_WIN:
		renderGameplay();
		break;
	case GameState::GAME_OVER:
		renderGameOver();
		break;
	case GameState::GAME_WIN:
		renderGameWin();
		break;
	}
}

void Game::renderGameStart()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	startPanel->render(renderer);
}

void Game::renderRoundStart()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	roundStartPanel->render(renderer, level);
}

void Game::renderGameOver()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	gameOverPanel->render(renderer);
}

void Game::renderGameWin()
{
	entities::renderAll(nonColliders, renderer);
	scoresPanel->render(renderer, numLives, score, level);
	gameWinPanel->render(renderer);
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
		numLives++;
		Sounds::play(extraLife);
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
	Sounds::play(ballLoss);
}

void Game::onGameEnd()
{
	numLives = Constants::START_LIVES;
	score = 0;
	level = 1;
	Sounds::play(gameEnd);
}