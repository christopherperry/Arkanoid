#include "Player.h"

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

	boundingBox.render(renderer);
}
