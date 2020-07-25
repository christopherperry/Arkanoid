#pragma once

#include <SDL.h>
#include "AABB.h"
#include "sprites/sprite.h"
#include "Vector2.h"

class Entity
{
protected:
	Vector2 position;
	Sprite* sprite;
	AABB boundingBox;
public:
	Entity() = delete;
	Entity(Sprite* sprite, AABB boundingBox, Vector2 position) : sprite(sprite), boundingBox(boundingBox), position(position) {};
	virtual bool collidesWith(Entity& other);
	virtual Hit* checkCollision(Entity& other);
	virtual void render(SDL_Renderer* renderer);
	virtual void renderColliders(SDL_Renderer* renderer);
	virtual void renderCollidersHit(SDL_Renderer* renderer);
	virtual bool isCollidable() { return true; };
	virtual void onCollision(Hit* hit) {}; // do nothing by default
	virtual bool isAlive() { return true; }
	virtual std::string tag() { return "none"; }
};