#pragma once

#include <algorithm>
#include <SDL.h>
#include "../collisions/AABB.h"
#include "../sprites/sprite.h"
#include "../math/Vector2.h"
#include "../utils/Functions.h"

class Entity
{
protected:
	Vector2 position;
	Vector2 scale;
	Sprite* sprite;
	AABB boundingBox;
public:
	Entity() = delete;
	Entity(Sprite* sprite, AABB boundingBox, Vector2 position, Vector2 scale = Vector2{ 1.0f, 1.0f }) : sprite(sprite), boundingBox(boundingBox), position(position), scale{ scale } {};
	Vector2 getPosition() { return position; }
	virtual Vector2 getVelocity() { return Vector2::zero; }
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
	void deleteAll(std::vector<Entity*>& entities);

	void updateEach(const std::vector<Entity*>& entities, float deltaTime);

	bool containsOnly(const std::vector<Entity*>& entities, std::string tag);

	void removeDead(std::vector<Entity*>& entities);

	void renderAll(std::vector<Entity*>& entities, SDL_Renderer* renderer);

	void checkAndNotifyCollisions(const std::vector<Entity*>& entities, Entity* entity, functions::Func* f = nullptr);
	void checkCollidesWithAndNotify(const std::vector<Entity*>& entities, Entity* entity, functions::Func1<Entity*>* f = nullptr);
	void checkCollidesWithAndEmptyNotify(const std::vector<Entity*>& entities, const std::vector<Entity*>& otherEntities);

	template <typename T>
	void removeDeadThenForEach(std::vector<Entity*>& entities, functions::Func1<T> f)
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