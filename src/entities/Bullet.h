#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:
	const Vector2 velocity{ 0.0f, 300.0f / 1000.0f };
	int numHits{ 0 };
public:
	Bullet(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void update(float deltaTimeMillis);
	void onCollision(Hit* hit) override;
	bool isAlive() const override;
};

