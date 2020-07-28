#pragma once

#include <map>
#include <vector>
#include "sprites/sprite.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "entities/Ball.h"
#include "entities/BallLossArea.h"
#include "Text.h"
#include "ScoresPanel.h"
#include "LevelLoader.h"
#include "GameStartPanel.h"
#include "GameOverPanel.h"
#include "powerups/PowerUpSpawner.h"
#include "BulletSpawner.h"

enum GameState
{
	// Start Panel Shown
	GAME_START,

	// Ball hasn't been launched yet
	BALL_LAUNCH,

	// Ball is in play
	PLAYING,

	// Lost a ball, player dissolves
	BALL_LOSS,

	// Game is over
	GAME_OVER
};

class Game
{
private:
	// The tiles are square 31x31
	static const int TILE_SIZE = 31;
	static const int OFFSET = TILE_SIZE * 0.5;
	static const int BRICK_HEIGHT = 16;
	static const int WALL_TOP_THICKNESS = 13;

	// Let's do 11 bricks and a wall on each side for now
	static const int NUM_TILES_WIDE = 13;
	static const int NUM_TILES_HIGH = 16;

	static const int START_LIVES = 6;

	float windowWidth;
	float windowHeight;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture; // This is the sprite sheet
	
	std::vector<Entity*> entities;
	std::vector<PowerUpCapsule*> powerUpCapsules;
	std::vector<Bullet*> bullets;

	int level{ 1 };
	int numLives{ START_LIVES };
	int score{ 0 };
	GameState gameState{ GameState::GAME_START };

	// Things we create and need to clean up
	BallLossArea* ballLossArea = nullptr;
	Player* player = nullptr;
	Ball* ball = nullptr;
	Mix_Chunk* paddleHit;
	Mix_Chunk* brickHit;
	Mix_Chunk* ballLoss;
	Mix_Chunk* gunshot;
	Mix_Music* gameStart;
	Mix_Music* gameEnd;

	TTF_Font* font;

	LevelLoader* levelLoader;
	ScoresPanel* scoresPanel;
	GameStartPanel* startPanel;
	GameOverPanel* gameOverPanel;
	PowerUpSpawner* powerUpSpawner;
	BulletSpawner* bulletSpawner;

	void renderGameStart();
	void renderGameplay();
	void renderGameOver();

	void onGameStart();
	void onGameEnd();
	void reloadLevel();

	void destroyEntities();
	void destroyPowerUps();
	void destroyBullets();

	void playSound(Mix_Chunk* sound);
	void playMusic(Mix_Music* music);

	Player* createPlayer();
	Ball* createBall();
	void onBallLoss();
	std::vector<std::pair<Entity*, Hit*>> checkCollisions(Entity* const entity, std::string tag);
public:
	Game(float windowWidth, float windowHeight, SDL_Renderer* renderer, SDL_Texture* texture);
	~Game();
	void onEvent(SDL_Event e);
	void update(float deltaTime);
	void checkCollisions();
	void render();
};