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
	bounds.x = position.x;
	bounds.y = position.y;
}

bool BoundingBox::collidesWith(BoundingBox& other)
{
	int thisLeft = bounds.x;
	int thisRight = bounds.x + bounds.w;
	int thisTop = bounds.y;
	int thisBottom = bounds.y + bounds.h;

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
	SDL_RenderDrawRect(renderer, &bounds);
}