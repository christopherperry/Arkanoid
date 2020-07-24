#include <SDL.h>
#include <algorithm>
#include "AABB.h"
#include "Vector2.h"

AABB::AABB(Vector2 position, Vector2 extents) : 
	position{ position }, extents{ extents } {}

void AABB::moveBy(int distanceX, int distanceY)
{
	this->position.x += distanceX;
	this->position.y += distanceY;
}

bool AABB::checkCollision(const AABB& other)
{
	int thisMinX = position.x - extents.x;
	int thisMaxX = position.x + extents.x;
	int thisMinY = position.y - extents.y;
	int thisMaxY = position.y + extents.y;

	int otherMinX = other.position.x - other.extents.x;
	int otherMaxX = other.position.x + other.extents.x;
	int otherMinY = other.position.y - other.extents.y;
	int otherMaxY = other.position.y + other.extents.y;

	return (thisMinX <= otherMaxX && thisMaxX >= otherMinX) &&
		(thisMinY <= otherMaxY && thisMaxY >= otherMinY);
}

void AABB::render(SDL_Renderer* renderer)
{
	SDL_Rect renderRect{};
	renderRect.x = position.x;
	renderRect.y = position.y;
	renderRect.w = extents.x + extents.x;
	renderRect.h = extents.y + extents.y;

	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &renderRect);
}
