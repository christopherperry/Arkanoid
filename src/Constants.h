#pragma once

namespace Constants
{
	//////////////////////////////////
	// Debug
	//////////////////////////////////
	static constexpr bool RENDER_COLLIDERS{ false };

	//////////////////////////////////
	// Ball
	//////////////////////////////////
	static constexpr float BALL_SPEED{ 300.0f / 1000.0f }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SPEED_MAX{ 400.0f / 1000.0f }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SPEED_MAX_SQUARED{ BALL_SPEED_MAX * BALL_SPEED_MAX }; // pixels per second, time is in milliseconds
	static constexpr float BALL_SIZE{ 6.0f };

	//////////////////////////////////
	// Player
	//////////////////////////////////
	static constexpr float PLAYER_MOVE_SPEED{ 400.0f / 1000.0f }; // pixels per second, time is in milliseconds
	static constexpr float TIME_BETWEEN_BULLET_SPAWNS{ 200.0f }; // Prevents spam firing. Pixels per second, time is in milliseconds. 

	//////////////////////////////////
	// Tiles
	//////////////////////////////////
	static constexpr int TILE_SIZE{ 31 }; // The tiles are square 31x31
	static constexpr float OFFSET{ TILE_SIZE * 0.5f };
	static constexpr int BRICK_WIDTH{ 31 };
	static constexpr int BRICK_HEIGHT{ 16 };
	static constexpr int WALL_TOP_THICKNESS{ 13 };

	//////////////////////////////////
	// Levels
	//////////////////////////////////
	static constexpr int NUM_BRICKS_WIDE{ 11 };
	static constexpr int NUM_TILES_WIDE{ NUM_BRICKS_WIDE + 2 }; // Add the walls on each side
	static constexpr int NUM_TILES_HIGH{ 16 };

	//////////////////////////////////
	// Gameplay
	//////////////////////////////////
	static constexpr int START_LIVES{ 6 };
	static constexpr int NUM_LEVELS{ 5 };
	static constexpr int CAPSULE_COLLECTION_POINTS{ 1000 };
	static constexpr int ONE_UP_HIGH_SCORE{ 25000 };
};