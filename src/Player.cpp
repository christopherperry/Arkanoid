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
	Logger::log("Delta time: " + std::to_string(deltaTime)); 

	float directionX = 0;
	if (movingLeft)
	{
		Logger::log("Moving LEFT");
		directionX = -1;
	}
	else if (movingRight)
	{
		Logger::log("Moving RIGHT");
		directionX = 1;
	}

	float distanceX = directionX * velocity * deltaTime;
	Logger::log("Distance: " + std::to_string(distanceX));
	position.x += distanceX;

	boundingBox.moveBy(distanceX, 0);
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_Rect leftHalfLocation;
	leftHalfLocation.x = position.x;
	leftHalfLocation.y = position.y;
	leftHalfLocation.w = leftHalf->rect.w;
	leftHalfLocation.h = leftHalf->rect.h;

	SDL_RenderCopy(renderer, leftHalf->texture, &leftHalf->rect, &leftHalfLocation);

	SDL_Rect rightHalfLocation;
	rightHalfLocation.x = position.x + leftHalf->rect.w;
	rightHalfLocation.y = position.y;
	rightHalfLocation.w = rightHalf->rect.w;
	rightHalfLocation.h = rightHalf->rect.h;

	SDL_RenderCopy(renderer, rightHalf->texture, &rightHalf->rect, &rightHalfLocation);
}
