#pragma once

#include <SDL.h>
#include <map>
#include "PowerUp.h"
#include "../collisions/AABB.h"
#include "../math/Vector2.h"
#include "../entities/Entity.h"
#include "../AnimationFrames.h"

class PowerUpCapsule : public Entity
{
protected:
	std::map<int, Sprite*> sprites;
	Vector2 velocity{0.0f, 100.0f / 1000.0f };
	AnimationFrames animationFrames{ 7, 75, true };
public:
	PowerUpCapsule(Vector2 position);
	~PowerUpCapsule();
	void update(float deltaTimeMillis);
	void render(SDL_Renderer* renderer);
	virtual PowerUp getPowerUp() = 0;
};

