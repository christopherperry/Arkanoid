#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(Sprite* sprite, Vector2 position) : Entity(sprite, AABB{Vector2::zero, Vector2::zero}, position) {};
	void renderColliders(SDL_Renderer* renderer) override {}; // do nothing
	void renderCollidersHit(SDL_Renderer* renderer) override {}; // do nothing
	void update(float deltaTime) override { }; // do nothing
	bool isCollidable() override { return false; };
};

