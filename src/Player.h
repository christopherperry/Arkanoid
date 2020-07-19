#pragma once

#include "Entity.h"
#include "sprites/sprite.h"

class Player: public Entity
{
private:
	Sprite* leftHalf;
	Sprite* rightHalf;
public:
	Player() = delete;
	Player(Sprite* leftHalf, Sprite* rightHalf, BoundingBox boundingBox, SDL_Point position) : Entity(nullptr, boundingBox, position)
	{
		this->leftHalf = leftHalf;
		this->rightHalf = rightHalf;
	}
	void moveBy(int distanceX, int distanceY);
	void render(SDL_Renderer* renderer) override;
};

