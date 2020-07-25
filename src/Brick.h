#pragma once

#include <SDL_mixer.h>
#include "Entity.h"

class Brick : public Entity
{
private:
	int numHitsToDestroy;
	int totalHits{ 0 };
public:
	Brick(Sprite* sprite, AABB boundingBox, Vector2 position, int numHitsToDestroy) : Entity(sprite, boundingBox, position), numHitsToDestroy{ numHitsToDestroy } {};
	void onCollision(Hit* hit) override;
	bool isAlive() override;
	std::string tag() override { return "brick"; }
};