#pragma once

#include "Entity.h"

class BackgroundTile : public Entity
{
public:
	BackgroundTile(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void renderColliders(SDL_Renderer* renderer) const override { }; // do nothing
	void update(float deltaTime) override { }; // do nothing
	bool collidesWith(const Entity& other) const override { return false; }
	bool isCollidable() const override { return false; }
};

