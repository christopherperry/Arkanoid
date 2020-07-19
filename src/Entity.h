#pragma once

#include <SDL.h>
#include "BoundingBox.h"
#include "sprites/sprite.h"

class Entity
{
protected:
	SDL_Point position;
	Sprite* sprite;
	BoundingBox boundingBox;
public:
	Entity() = delete;
	Entity(Sprite* sprite, BoundingBox boundingBox, SDL_Point position);
	bool collidesWith(Entity& other);
	virtual void render(SDL_Renderer* renderer);
};