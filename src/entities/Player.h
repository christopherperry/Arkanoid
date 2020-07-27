#pragma once

#include <SDL.h>
#include <map>
#include "Entity.h"
#include "../sprites/sprite.h"
#include "../PlayerSpriteRenderer.h"

enum PlayerState
{
	REGULAR,

	LONG,

	SHORT,

	LAZER
};

class Player: public Entity
{
private:
	bool movingLeft = false;
	bool movingRight = false;
	float moveSpeed = 400 / 1000.0f; // pixels per second, time is in milliseconds
	float animationSpeed = 250 / 1000.0f; // 4 frames, finish over one second time
	float totalAnimTimeMillis = 0.0f;
	int currentAnimFrame = 0;
	bool isDissolving = false;
	bool isDissolved = false;
	PlayerSpriteRenderer* spriteRenderer;
	PlayerState state{ REGULAR };
public:
	Player() = delete;
	Player(SDL_Texture* texture, Vector2 position);
	Vector2 getPaddleTopCenterPosition();
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
	void dissolve();
	std::string tag() override { return "player"; }
};

