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
	float velocity = 200 / 1000.0f; // pixels per second, time is in milliseconds
public:
	Player() = delete;
	Player(Sprite* leftHalf, Sprite* rightHalf, BoundingBox boundingBox, Vector2 position) : Entity(nullptr, boundingBox, position)
	{
		this->leftHalf = leftHalf;
		this->rightHalf = rightHalf;
	}
	void update(float deltaTime);
	void onEvent(SDL_Event event);
	void render(SDL_Renderer* renderer) override;
};

