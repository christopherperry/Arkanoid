#pragma once

#include "Entity.h"
#include "AABB.h"

class Ball : public Entity
{
private:
	Vector2 velocity{ 0.0f, 0.0f };
public:
	Ball() = delete;
	Ball(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void setVelocity(Vector2 velocity);
	void update(float deltaTime);
	void onCollision(Hit* hit, float deltaTime);
};