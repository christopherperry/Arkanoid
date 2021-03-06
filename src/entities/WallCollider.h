#pragma once

#include "Entity.h"

class WallCollider : public Entity
{
public:
	WallCollider(AABB boundingBox, Vector2 position) : Entity(nullptr, boundingBox, position) {};
	void render(SDL_Renderer* renderer) const override { }; // do nothing
	void update(float deltaTime) override { }; // do nothing
	std::string tag() const { return "wall"; }
};

