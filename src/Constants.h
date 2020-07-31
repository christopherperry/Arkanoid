#pragma once

class Constants
{
public:
	const static bool RENDER_COLLIDERS;
	const static float BALL_SPEED; // pixels per second, time is in milliseconds
	const static float BALL_SPEED_MAX; // pixels per second, time is in milliseconds
	const static float BALL_SPEED_MAX_SQUARED; // pixels per second, time is in milliseconds
	const static float BALL_SIZE;

	// The tiles are square 31x31
	static const int TILE_SIZE = 31;
	static const int OFFSET = TILE_SIZE * 0.5;
	static const int BRICK_WIDTH = 31;
	static const int BRICK_HEIGHT = 16;
	static const int WALL_TOP_THICKNESS = 13;

	// Let's do 11 bricks and a wall on each side for now
	static const int NUM_TILES_WIDE = 13;
	static const int NUM_TILES_HIGH = 16;

	static const int NUM_BRICKS_WIDE = 11;

	static const int START_LIVES = 60;

	static const int NUM_LEVELS = 5;
	static const int CAPSULE_COLLECTION_POINTS = 1000;
	static const int ONE_UP_HIGH_SCORE = 25000;
};

