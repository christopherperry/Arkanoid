#pragma once

#include <algorithm>
#include <SDL.h>
#include "../collisions/AABB.h"
#include "../sprites/Sprite.h"
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
	
	Vector2 getPosition() const { return position; }
	virtual Vector2 getVelocity() const { return Vector2::zero; }
	virtual bool collidesWith(const Entity& other) const;
	virtual void render(SDL_Renderer* renderer) const;
	virtual void renderColliders(SDL_Renderer* renderer) const;
	virtual void renderCollidersHit(SDL_Renderer* renderer) const;
	virtual Hit* checkCollision(const Entity& other) const;
	virtual bool isCollidable() const { return true; };
	virtual bool isAlive() const { return true; }
	virtual std::string tag() const { return "none"; }
	virtual int getScoreValue() const { return 0; }
	
	virtual void update(float deltaTime) = 0;
	virtual void onCollision(Hit* hit) {}; // do nothing by default
};

namespace entities
{
	void deleteAll(std::vector<Entity*>& entities);

	void updateEach(const std::vector<Entity*>& entities, float deltaTime);

	bool containsOnly(const std::vector<Entity*>& entities, std::string tag);

	void removeDead(std::vector<Entity*>& entities);

	void removeIfColliding(std::vector<Entity*>& entities, const Entity& entity);

	void renderAll(const std::vector<Entity*>& entities, SDL_Renderer* renderer);

	void checkAndNotifyCollisions(const std::vector<Entity*>& entities, Entity& entity, functions::Func* f = nullptr);
	void checkCollidesWithAndNotify(const std::vector<Entity*>& entities, Entity& entity, functions::Func1<Entity*>* f = nullptr);
	void checkCollidesWithAndEmptyNotify(const std::vector<Entity*>& entities, const std::vector<Entity*>& otherEntities);

	template <typename T>
	void removeDeadThenForEach(std::vector<Entity*>& entities, functions::Func1<T> f)
	{
		std::vector<Entity*>::iterator newEnd = std::partition(entities.begin(), entities.end(), [=](const Entity* e) -> bool { return e->isAlive(); });
		for (std::vector<Entity*>::iterator it = newEnd; it != entities.end(); ++it)
		{
			f(*it);
			SafeDelete(*it);
		}
		entities.erase(newEnd, entities.end());
	}
}