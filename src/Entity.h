#pragma once

#include <SDL.h>
#include "BoundingBox.h"
#include "sprites/sprite.h"
#include "Vector2.h"

class Entity
{
protected:
	Vector2 position;
	Sprite* sprite;
	BoundingBox boundingBox;
public:
	Entity() = delete;
	Entity(Sprite* sprite, BoundingBox boundingBox, Vector2 position) : sprite(sprite), boundingBox(boundingBox), position(position) {};
	bool collidesWith(Entity& other);
	virtual void render(SDL_Renderer* renderer);
};