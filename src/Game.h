#pragma once

#include <map>
#include <vector>
#include "sprites/sprite.h"
#include "Entity.h"
#include "Player.h"
#include "Ball.h"
#include "BallLossArea.h"
#include "Text.h"

// WARNING: only add at the end 
// because we hardcoded numbers to define the level
enum SpriteId
{
	// Bricks
	BRICK_YELLOW,
	BRICK_GREEN,
	BRICK_RED,
	BRICK_BROWN,
	BRICK_LAVENDER,
	BRICK_ORANGE,
	BRICK_BLUE,
	BRICK_PURPLE,
	BRICK_GREY_IDLE,
	BRICK_GREY_ANIM_1,
	BRICK_GRAY_ANIM_2,

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

	// Player - Medium
	PLAYER_LEFT_MEDIUM,
	PLAYER_RIGHT_MEDIUM,
	PLAYER_LEFT_MEDIUM_DISSOLVE_1,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_1,
	PLAYER_LEFT_MEDIUM_DISSOLVE_2,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_2,
	PLAYER_LEFT_MEDIUM_DISSOLVE_3,
	PLAYER_RIGHT_MEDIUM_DISSOLVE_3,

	// Player - Medium Gunner
	PLAYER_LEFT_MEDIUM_GUNNER,
	PLAYER_RIGHT_MEDIUM_GUNNER,

	// Player - Large
	PLAYER_LEFT_LARGE,
	PLAYER_RIGHT_LARGE,

	// Player - Small
	PLAYER_SMALL,

	// Ball
	BALL,

	NONE = -1
};

enum GameText
{
	// Digits for rendering the actual score
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	DIGIT_4,
	DIGIT_5,
	DIGIT_6,
	DIGIT_7,
	DIGIT_8,
	DIGIT_9,

	// "Score: "
	SCORE,

	// "High Score: "
	HIGH_SCORE,

	// "Lives: "
	LIVES
};

enum GameState
{
	// Ball hasn't been launched yet
	STARTING,

	// Ball is in play
	PLAYING,

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

	float windowWidth;
	float windowHeight;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture; // This is the sprite sheet
	std::map<int, Sprite> sprites;
	std::map<int, Text*> text;
	std::vector<Entity*> entities;

	// Start with 6 lives
	int numLives{ 6 };
	int score{ 0 };
	GameState gameState{ GameState::STARTING };

	// Things we create and need to clean up
	BallLossArea* ballLossArea = nullptr;
	Player* player = nullptr;
	Ball* ball = nullptr;
	Mix_Chunk* paddleHit;
	Mix_Chunk* brickHit;
	Mix_Chunk* ballLoss;
	TTF_Font* font;

	Player* createPlayer();
	Ball* createBall();
	void launchBall();
	void onBallLoss();
	std::vector<std::pair<Entity*, Hit*>> checkCollisions(Entity* const entity);
public:
	Game(float windowWidth, float windowHeight, SDL_Renderer* renderer, SDL_Texture* texture);
	~Game();
	void loadLevel();
	void loadText();
	void onEvent(SDL_Event e);
	void update(float deltaTime);
	void checkCollisions();
	void render();
	void renderText();
	
	Sprite* getSprite(int id);
};