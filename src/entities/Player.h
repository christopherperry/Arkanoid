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
	mutable float lastBulletSpawnTime;

	PlayerSpriteRenderer* spriteRenderer;
	PlayerState state{ PlayerState::REGULAR };
	Vector2 startPosition;
	Vector2 velocity;
	Player(SDL_Texture* texture, Vector2 position, Vector2 scale);
public:

	static Player* createNew(SDL_Texture* const texture);
	Player() = delete;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	PlayerState getState() const;
	Vector2 getPaddleTopCenterPosition() const;
	Vector2 getVelocity() const override;
	bool isReadyToLaunch() const;
	void render(SDL_Renderer* renderer) const override;
	bool canFireBullets() const;
	std::pair<Entity*, Entity*> fireBullets() const;
	std::string tag() const override { return "player"; }

	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void setState(PlayerState state);
	void reset();
};

