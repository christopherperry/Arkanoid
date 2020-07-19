#include "BoundingBox.h"

#include <SDL.h>

BoundingBox::BoundingBox()
{
	this->bounds = SDL_Rect();
}

BoundingBox::BoundingBox(SDL_Rect bounds)
{
	this->bounds = bounds;
}

void BoundingBox::moveTo(SDL_Point position)
{
	this->bounds.x = position.x;
	this->bounds.y = position.y;
}

void BoundingBox::moveBy(int distanceX, int distanceY)
{
	this->bounds.x += distanceX;
	this->bounds.y += distanceY;
}

bool BoundingBox::collidesWith(BoundingBox& other)
{
	int thisLeft = this->bounds.x;
	int thisRight = this->bounds.x + this->bounds.w;
	int thisTop = this->bounds.y;
	int thisBottom = this->bounds.y + this->bounds.h;

	int otherLeft = other.bounds.x;
	int otherRight = other.bounds.x + other.bounds.w;
	int otherTop = other.bounds.y;
	int otherBottom = other.bounds.y + other.bounds.h;

	if (otherLeft >= thisRight) return false;
	if (otherRight <= thisLeft) return false;
	if (otherBottom <= thisTop) return false;
	if (otherTop >= thisBottom) return false;

	return true;
}

void BoundingBox::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &this->bounds);
}

SDL_Rect BoundingBox::getBounds()
{
	return this->bounds;
}
