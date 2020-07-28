#pragma once

#include <SDL.h>
#include <map>
#include "Entity.h"
#include "../sprites/sprite.h"
#include "../PlayerSpriteRenderer.h"

enum class PlayerState
{
	REGULAR,

	EXPANDED,

	SHORT,

	LAZER, 

	DISSOLVE
};

class Player: public Entity
{
private:
	bool movingLeft = false;
	bool movingRight = false;
	float moveSpeed = 400 / 1000.0f; // pixels per second, time is in milliseconds
	PlayerSpriteRenderer* spriteRenderer;
	PlayerState state{ PlayerState::REGULAR };
	Vector2 startPosition;
public:
	Player() = delete;
	Player(SDL_Texture* texture, Vector2 position);
	Vector2 getPaddleTopCenterPosition();
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
	void setState(PlayerState state);
	bool isReadyToLaunch();
	void reset();
	std::string tag() override { return "player"; }
};

