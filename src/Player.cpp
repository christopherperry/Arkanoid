#include "Player.h"

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

void Player::update()
{
	// Process Events
	if (movingLeft)
	{
		moveBy(-1, 0);
	}
	else if (movingRight)
	{
		moveBy(1, 0);
	}
}

// TODO: collision detection and resolution
void Player::moveBy(int distanceX, int distanceY)
{
	position.x += distanceX;
	position.y += distanceY;

	boundingBox.moveBy(distanceX, distanceY);
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

	//boundingBox.render(renderer);
}
