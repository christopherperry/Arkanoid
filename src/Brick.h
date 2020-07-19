#pragma once

#include "Entity.h"

class Brick : public Entity
{
public:
	Brick(Sprite* sprite, BoundingBox boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void render(SDL_Renderer* renderer) override;
};