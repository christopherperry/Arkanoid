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
	Mix_Chunk* hitUnbreakableBrickSound;
	Ball(Sprite* sprite, AABB boundingBox, Vector2 position, Vector2 scale, Mix_Chunk* hitBrickSound, Mix_Chunk* hitUnbreakableBrickSound, Mix_Chunk* hitPaddleSound) : Entity(sprite, boundingBox, position, scale), hitBrickSound{ hitBrickSound }, hitUnbreakableBrickSound{ hitUnbreakableBrickSound }, hitPaddleSound{ hitPaddleSound } {};
public:
	Ball() = delete;
	static Ball* createNew(SDL_Texture* texture, Vector2 position, Mix_Chunk* hitBrickSound, Mix_Chunk* hitUnbreakableBrickSound, Mix_Chunk* hitPaddleSound);
	void launch();
	void increaseSpeed();
	std::vector<Entity*> disrupt();
	void reset(Vector2 position);
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	std::string tag() override { return "ball"; }
};