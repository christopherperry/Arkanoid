#pragma once

#include "Entity.h"

class BackgroundTile : public Entity
{
public:
	BackgroundTile(Sprite* sprite, AABB boundingBox, Vector2 position) : Entity(sprite, boundingBox, position) {};
	void renderColliders(SDL_Renderer* renderer) override { }; // do nothing
	bool collidesWith(Entity& other) override { return false; }
	bool isCollidable() override { return false; }
};

