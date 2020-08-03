#include <SDL.h>
#include <algorithm>
#include "AABB.h"
#include "../math/Vector2.h"

int sign(float a)
{
	return a < 0 ? -1 : 1;
}

AABB::AABB(Vector2 position, Vector2 extents) : 
	position{ position }, extents{ extents } {}

void AABB::moveBy(float distanceX, float distanceY)
{
	this->position.x += distanceX;
	this->position.y += distanceY;
}

void AABB::moveTo(Vector2 position)
{
	this->position = position;
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

Hit* AABB::checkIntersection(const AABB& other)
{
	// Difference in positions along the x-axis
	const float dx = other.position.x - position.x;
	// Penetration distance along the x-axis
	const float px = other.extents.x + extents.x - abs(dx);
	if (px <= 0.0f)
	{
		return nullptr;
	}

	// Difference in positions along the y-axis
	const float dy = other.position.y - position.y;
	// Penetration distance along the y-axis
	const float py = other.extents.y + extents.y - abs(dy);
	if (py <= 0.0f)
	{
		return nullptr;
	}


	// Penetration along both axis means there's a collision
	Hit* hit = new Hit();

	if (px < py)
	{
		// if dx is positive that means the other box was to our right, negative means it was to our left
		const int sx = sign(dx);
		hit->delta.x = px * sx; // the amount to correct the collision, you'd subtract this from your position if you owned this AABB
		hit->normal.x = sx; // the normal of the surface of this AABB where the collision occurred
		hit->contactPoint.x = position.x + (sx * extents.x);
		hit->contactPoint.y = other.position.y; // center y on the other box
	}
	else
	{
		const int sy = sign(dy);
		hit->delta.y = py * sy;
		hit->normal.y = sy;
		hit->contactPoint.x = other.position.x;
		hit->contactPoint.y = position.y + (sy * extents.y);
	}

	return hit;
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

