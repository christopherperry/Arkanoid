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

	SHRUNK,

	GUNNER, 

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
	Vector2 velocity;
	Player(SDL_Texture* texture, Vector2 position, Vector2 scale);
public:
	Player() = delete;
	static Player* createNew(SDL_Texture* texture);
	Vector2 getPaddleTopCenterPosition();
	Vector2 getVelocity() override;
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
	void setState(PlayerState state);
	PlayerState getState();
	bool isReadyToLaunch();
	void reset();
	std::string tag() override { return "player"; }
};

