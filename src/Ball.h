#pragma once

#include <SDL_mixer.h>
#include "Entity.h"
#include "AABB.h"

class Ball : public Entity
{
private:
	Vector2 velocity{ 0.0f, 0.0f };
	Mix_Chunk* hitBrickSound;
	Mix_Chunk* hitPaddleSound;
public:
	Ball() = delete;
	Ball(Sprite* sprite, AABB boundingBox, Vector2 position, Vector2 velocity, Mix_Chunk* hitBrickSound, Mix_Chunk* hitPaddleSound) : Entity(sprite, boundingBox, position), velocity{ velocity }, hitBrickSound{ hitBrickSound }, hitPaddleSound{ hitPaddleSound } {};
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	std::string tag() override { return "ball"; }
};