#pragma once

#include "Entity.h"

class Brick : public Entity
{
public:
	Brick(Sprite* sprite, BoundingBox boundingBox, SDL_Point position) : Entity(sprite, boundingBox, position) {};
	void render(SDL_Renderer* renderer) override;
};

