#pragma once

#include <SDL.h>
#include "BoundingBox.h"
#include "sprites/sprite.h"

class Entity
{
private:
	SDL_Point position;
	Sprite* sprite;
	BoundingBox boundingBox;
public:
	Entity(Sprite* sprite, BoundingBox boundingBox, SDL_Point position);
	bool collidesWith(Entity& other);
	void render(SDL_Renderer* renderer);
};