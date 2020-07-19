#pragma once

#include "Entity.h"

class Ball : public Entity
{
	Ball() = delete;
	Ball(Sprite* sprite, BoundingBox boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void hit(Vector2 direction);
};