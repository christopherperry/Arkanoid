#pragma once

#include "Entity.h"
#include "sprites/sprite.h"

class Player: public Entity
{
private:
	Sprite* leftHalf;
	Sprite* rightHalf;
	bool movingLeft = false;
	bool movingRight = false;
	float moveSpeed = 400 / 1000.0f; // pixels per second, time is in milliseconds
public:
	Player() = delete;
	Player(Sprite* leftHalf, Sprite* rightHalf, AABB boundingBox, Vector2 position) : Entity(nullptr, boundingBox, position)
	{
		this->leftHalf = leftHalf;
		this->rightHalf = rightHalf;
	}
	Vector2 getPaddleTopCenterPosition();
	void update(float deltaTime);
	void onCollision(Hit* hit) override;
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
	std::string tag() override { return "player"; }
};

