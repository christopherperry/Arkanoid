#pragma once

#include <SDL.h>
#include <map>
#include "Entity.h"
#include "../sprites/Sprite.h"
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

	Sprite* bulletSprite;
	float lastBulletSpawnTime;

	PlayerSpriteRenderer* spriteRenderer;
	PlayerState state{ PlayerState::REGULAR };
	Vector2 startPosition;
	Vector2 velocity;
	Player(SDL_Texture* texture, Vector2 position, Vector2 scale);
public:
	Player() = delete;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	static Player* createNew(SDL_Texture* texture);
	Vector2 getPaddleTopCenterPosition();
	Vector2 getVelocity() override;
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
	void setState(PlayerState state);
	bool canFireBullets();
	std::pair<Entity*, Entity*> fireBullets();
	PlayerState getState();
	bool isReadyToLaunch();
	void reset();
	std::string tag() override { return "player"; }
};

