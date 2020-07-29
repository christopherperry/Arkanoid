#include "Constants.h"

const bool Constants::RENDER_COLLIDERS = false;

const float Constants::BALL_SPEED{ 300.0f / 1000.0f }; // pixels per second, time is in milliseconds
const float Constants::BALL_SPEED_MAX{ 400.0f / 1000.0f }; // pixels per second, time is in milliseconds
const float Constants::BALL_SPEED_MAX_SQUARED{ BALL_SPEED_MAX * BALL_SPEED_MAX }; // pixels per second, time is in milliseconds
const float Constants::BALL_SIZE{ 6.0f };