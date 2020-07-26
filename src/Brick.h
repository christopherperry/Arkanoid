#pragma once

#include <SDL_mixer.h>
#include "Entity.h"

class Brick : public Entity
{
private:
	int scoreValue;
	int numHitsToDestroy;
	int totalHits{ 0 };
public:
	Brick(Sprite* sprite, AABB boundingBox, Vector2 position, int numHitsToDestroy, int scoreValue) : Entity(sprite, boundingBox, position), numHitsToDestroy{ numHitsToDestroy }, scoreValue{ scoreValue } {};
	void onCollision(Hit* hit) override;
	bool isAlive() override;
	std::string tag() override { return "brick"; }
	int getScoreValue() override { return scoreValue; }
};