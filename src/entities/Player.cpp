#include "Player.h"
#include "../utils/logger.h"

enum PlayerSprites
{
	REG_LEFT,
	REG_RIGHT,
	REG_LEFT_DISSOLVE_1,
	REG_RIGHT_DISSOLVE_1,
	REG_LEFT_DISSOLVE_2,
	REG_RIGHT_DISSOLVE_2,
	REG_LEFT_DISSOLVE_3,
	REG_RIGHT_DISSOLVE_3,
};

void renderTwoSprite(SDL_Renderer* renderer, AABB boundingBox, Sprite* leftHalf, Sprite* rightHalf)
{
	SDL_Rect leftHalfLocation;
	leftHalfLocation.x = boundingBox.position.x - boundingBox.extents.x;
	leftHalfLocation.y = boundingBox.position.y - boundingBox.extents.y;
	leftHalfLocation.w = boundingBox.extents.x;
	leftHalfLocation.h = boundingBox.extents.y * 2;

	SDL_RenderCopy(renderer, leftHalf->texture, &leftHalf->rect, &leftHalfLocation);

	SDL_Rect rightHalfLocation;
	rightHalfLocation.x = boundingBox.position.x;
	rightHalfLocation.y = boundingBox.position.y - boundingBox.extents.y;
	rightHalfLocation.w = boundingBox.extents.x;
	rightHalfLocation.h = boundingBox.extents.y * 2;

	SDL_RenderCopy(renderer, rightHalf->texture, &rightHalf->rect, &rightHalfLocation);
}

// TODO: update this when we have more states
AABB boxForState(PlayerState state, Vector2 position)
{
	return AABB{ position, Vector2{ 21.0f, 5.5f } };
}

Player::Player(SDL_Texture* texture, Vector2 position) : Entity(nullptr, AABB{ position, Vector2{ 21.0f, 5.5f } }, position)
{
	sprites = {
		{REG_LEFT, new Sprite{texture, SDL_Rect{235, 175, 21, 11}}},
		{REG_RIGHT, new Sprite{texture, SDL_Rect{257, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_1, new Sprite{texture, SDL_Rect{299, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_1, new Sprite{texture, SDL_Rect{321, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_2, new Sprite{texture, SDL_Rect{363, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_2, new Sprite{texture, SDL_Rect{385, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_3, new Sprite{texture, SDL_Rect{427, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_3, new Sprite{texture, SDL_Rect{449, 175, 21, 11}}},
	};

	Vector2 extents{ 21.0f, 5.5f }; // Paddle size is 42 by 11
	AABB box{ position, extents };
	boundingBox = AABB{ position, extents };
}

void Player::onEvent(SDL_Event event)
{
	switch (event.key.keysym.sym) {
	case SDLK_LEFT:
		movingLeft = event.type == SDL_KEYDOWN;
		break;
	case SDLK_RIGHT:
		movingRight = event.type == SDL_KEYDOWN;
		break;
	default:
		break;
	}
}

Vector2 Player::getPaddleTopCenterPosition()
{
	return Vector2(boundingBox.position.x, boundingBox.position.y - boundingBox.extents.y);
}

void Player::update(float deltaTime)
{
	float directionX = 0;
	if (movingLeft)
	{
		directionX = -1;
	}
	else if (movingRight)
	{
		directionX = 1;
	}

	float distanceX = directionX * moveSpeed * deltaTime;
	position.x += distanceX;

	boundingBox.moveBy(distanceX, 0);
}

void Player::onCollision(Hit* hit)
{
	// Move position out of collision
	position = position - hit->delta;
	boundingBox.moveBy(-hit->delta.x, -hit->delta.y);
}

void Player::render(SDL_Renderer* renderer)
{
	renderTwoSprite(renderer, boundingBox, sprites[REG_LEFT], sprites[REG_RIGHT]);
}