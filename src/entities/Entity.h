#pragma once

#include <algorithm>
#include <functional>
#include <SDL.h>
#include "../collisions/AABB.h"
#include "../sprites/sprite.h"
#include "../math/Vector2.h"

class Entity
{
protected:
	Vector2 position;
	Sprite* sprite;
	AABB boundingBox;
public:
	Entity() = delete;
	Entity(Sprite* sprite, AABB boundingBox, Vector2 position) : sprite(sprite), boundingBox(boundingBox), position(position) {};
	Vector2 getPosition() { return position; }
	virtual bool collidesWith(Entity& other);
	virtual void update(float deltaTime) = 0;
	virtual Hit* checkCollision(Entity& other);
	virtual void render(SDL_Renderer* renderer);
	virtual void renderColliders(SDL_Renderer* renderer);
	virtual void renderCollidersHit(SDL_Renderer* renderer);
	virtual bool isCollidable() { return true; };
	virtual void onCollision(Hit* hit) {}; // do nothing by default
	virtual bool isAlive() { return true; }
	virtual std::string tag() { return "none"; }
	virtual int getScoreValue() { return 0; }
};

namespace entities
{
	template <typename T>
	using Func = std::function<void(T)>;

	void updateEach(const std::vector<Entity*>& entities, float deltaTime);

	void removeDead(std::vector<Entity*>& entities);

	template <typename T>
	void removeDeadThenForEach(std::vector<Entity*>& entities, Func<T> f)
	{
		std::vector<Entity*>::iterator newEnd = std::partition(entities.begin(), entities.end(), [=](Entity* e) -> bool { return e->isAlive(); });
		for (std::vector<Entity*>::iterator it = newEnd; it != entities.end(); ++it)
		{
			f(*it);
			delete (*it);
		}
		entities.erase(newEnd, entities.end());
	}
}