#pragma once

#include "Entity.h"

class Brick : public Entity
{
public:
	Brick(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
};