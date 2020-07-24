#pragma once

#include "Entity.h"
#include "AABB.h"

class Ball : public Entity
{
public:
	Ball() = delete;
	Ball(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
};