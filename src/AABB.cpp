#include <SDL.h>
#include <algorithm>
#include "AABB.h"
#include "Vector2.h"

AABB::AABB(Vector2 position, Vector2 extents) : 
	position{ position }, extents{ extents } {}

void AABB::moveBy(float distanceX, float distanceY)
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
	render(renderer, 0x00, 0xFF, 0x00, 0xFF);
}

void AABB::renderHit(SDL_Renderer* renderer)
{
	render(renderer, 0xFF, 0x00F, 0x00, 0xFF);
}

void AABB::render(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect renderRect;
	renderRect.x = position.x - extents.x;
	renderRect.y = position.y - extents.y;
	renderRect.w = extents.x + extents.x;
	renderRect.h = extents.y + extents.y;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &renderRect);
}

