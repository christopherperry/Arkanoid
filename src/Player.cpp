#include "Player.h"
#include "logger.h"

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
