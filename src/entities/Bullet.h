#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:
	Vector2 velocity{ 0.0f, 300.0f / 1000.0f };
public:
	Bullet(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void update(float deltaTimeMillis);
};

