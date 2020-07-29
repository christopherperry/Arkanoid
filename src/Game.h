#pragma once

#include <map>
#include <vector>
#include "Constants.h"
#include "sprites/sprite.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "entities/Ball.h"
#include "entities/BallLossArea.h"
#include "Text.h"
#include "ScoresPanel.h"
#include "levels/LevelLoader.h"
#include "levels/LevelBrickLoader.h"
#include "GameStartPanel.h"
#include "GameOverPanel.h"
#include "powerups/PowerUpSpawner.h"
#include "BulletSpawner.h"

enum GameState
{
	////////////////////////////////
	// Game is starting.
	//
	// Start screen with instructions
	// is shown.
	////////////////////////////////
	GAME_START,

	////////////////////////////////
	// Level is loaded.
	//
	// Round number is shown.
	////////////////////////////////
	ROUND_START,

	////////////////////////////////
	// Game has started.
	//
	// Player can now launch the ball.
	////////////////////////////////
	BALL_LAUNCH,

	////////////////////////////////
	// Gameplay is happening.
	////////////////////////////////
	PLAYING,

	////////////////////////////////
	// Lost a ball. Player dissolves.
	//
	// All active bullets and power ups
	// are destroyed.
	////////////////////////////////
	BALL_LOSS,

	////////////////////////////////
	// Player has destroyed all bricks.
	//
	// Updates are paused briefly.
	////////////////////////////////
	ROUND_WIN,

	// Game win
	GAME_WIN,

	// Game is over
	GAME_OVER
};

class Game
{
private:
	float windowWidth;
	float windowHeight;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture; // This is the sprite sheet
	
	std::vector<Entity*> nonColliders;
	std::vector<Entity*> wallColliders;
	std::vector<Entity*> bricks;
	std::vector<PowerUpCapsule*> powerUpCapsules;
	std::vector<Bullet*> bullets;

	int level{ 1 };
	int numLives{ Constants::START_LIVES };
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
	void destroyBricks();
	void destroyPowerUps();
	void destroyBullets();

	void playSound(Mix_Chunk* sound);
	void playMusic(Mix_Music* music);

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