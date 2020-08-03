#pragma once

class Constants
{
public:
	static constexpr bool RENDER_COLLIDERS{ false };
	static constexpr float BALL_SPEED{ 300.0f / 1000.0f }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SPEED_MAX{ 400.0f / 1000.0f }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SPEED_MAX_SQUARED{ BALL_SPEED_MAX * BALL_SPEED_MAX }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SIZE{ 6.0f };

	static constexpr float PLAYER_MOVE_SPEED{ 400.0f / 1000.0f }; // pixels per second, time is in milliseconds

	// The tiles are square 31x31
	static constexpr int TILE_SIZE{ 31 };
	static constexpr float OFFSET{ TILE_SIZE * 0.5f };
	static constexpr int BRICK_WIDTH{ 31 };
	static constexpr int BRICK_HEIGHT{ 16 };
	static constexpr int WALL_TOP_THICKNESS{ 13 };

	// Let's do 11 bricks and a wall on each side for now
	static constexpr int NUM_TILES_WIDE{ 13 };
	static constexpr int NUM_TILES_HIGH{ 16 };

	static constexpr int NUM_BRICKS_WIDE{ 11 };

	static constexpr int START_LIVES{ 6 };

	static constexpr int NUM_LEVELS{ 5 };
	static constexpr int CAPSULE_COLLECTION_POINTS{ 1000 };
	static constexpr int ONE_UP_HIGH_SCORE{ 25000 };
};

