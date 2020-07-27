#pragma once

#include <SDL.h>
#include "PowerUp.h"
#include "../collisions/AABB.h"
#include "../math/Vector2.h"
#include "../entities/Entity.h"
#include "../AnimationFrames.h"

class PowerUpCapsule : public Entity
{
protected:
	Vector2 velocity{0.0f, 100.0f / 1000.0f };
	AnimationFrames animationFrames{ 7, 75, true };
public:
	PowerUpCapsule(Vector2 position);
	void update(float deltaTimeMillis);
	void render(SDL_Renderer* renderer) override = 0;
	virtual PowerUp getPowerUp() = 0;
};

