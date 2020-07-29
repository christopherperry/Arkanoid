#pragma once

#include <SDL_mixer.h>
#include "Entity.h"
#include "../collisions/AABB.h"

class Ball : public Entity
{
private:
	Vector2 velocity{ 0.0f, 0.0f };
	Mix_Chunk* hitBrickSound;
	Mix_Chunk* hitPaddleSound;
	Ball(Sprite* sprite, AABB boundingBox, Vector2 position, Mix_Chunk* hitBrickSound, Mix_Chunk* hitPaddleSound) : Entity(sprite, boundingBox, position), hitBrickSound{ hitBrickSound }, hitPaddleSound{ hitPaddleSound } {};
public:
	Ball() = delete;
	static Ball* createNew(SDL_Texture* texture, Vector2 position, Mix_Chunk* hitBrickSound, Mix_Chunk* hitPaddleSound);
	void launch();
	void increaseSpeed();
	void reset(Vector2 position);
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	std::string tag() override { return "ball"; }
};