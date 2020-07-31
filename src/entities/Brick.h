#pragma once

#include <SDL_mixer.h>
#include "Entity.h"

class Brick : public Entity
{
private:
	int scoreValue;
	int numHitsToDestroy;
	int totalHits{ 0 };
	SDL_Rect outlineRect;
	std::string brickTag;
public:
	Brick(Sprite* sprite, AABB boundingBox, Vector2 position, int numHitsToDestroy, int scoreValue, std::string tag = "brick");
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override {}; // do nothing
	void onCollision(Hit* hit) override;
	bool isAlive() override;
	std::string tag() override { return brickTag; }
	int getScoreValue() override { return scoreValue; }
};