#include <iostream>
#include "Brick.h"

Brick::Brick(Sprite * sprite, AABB boundingBox, Vector2 position, int numHitsToDestroy, int scoreValue, std::string tag) : 
	Entity(sprite, boundingBox, position), numHitsToDestroy{ numHitsToDestroy }, scoreValue{ scoreValue }, brickTag{ tag }
{
	int sizeX = (int) boundingBox.extents.x;
	int sizeY = (int) boundingBox.extents.y;
	outlineRect = SDL_Rect{ (int) position.x - sizeX, (int) position.y - sizeY, sizeX * 2, sizeY * 2 };
}

void Brick::render(SDL_Renderer* renderer) const
{
	Entity::render(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &outlineRect);
}

void Brick::onCollision(Hit* hit)
{
	totalHits++;
}

bool Brick::isAlive() const
{
	if (numHitsToDestroy == -1) return true;
	return totalHits < numHitsToDestroy;
}
