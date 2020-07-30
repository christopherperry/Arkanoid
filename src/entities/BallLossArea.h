#pragma once

#include "Entity.h"

class BallLossArea : public Entity
{
public:
	BallLossArea(AABB boundingBox, Vector2 position) : Entity(nullptr, boundingBox, position) {};
	void update(float deltaTime) override { }; // do nothing
	std::string tag() override { return "ball loss"; }
};