#pragma once

#include "BoundingBox.h"
#include "sprites/sprite.h"

class Entity
{
private:
	int positionX;
	int positionY;
	Sprite* sprite;
	bool moveable;
	BoundingBox boundingBox;
public:
	Entity(Sprite* sprite, BoundingBox boundingBox, int spriteId, int positionX, int positionY, bool moveable);
	void move(int x, int y);
	bool collidesWith(Entity& other);
	void render(SDL_Renderer* renderer);
};

