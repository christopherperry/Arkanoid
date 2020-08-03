#include "Entity.h"
#include "../utils/Util.h"

bool Entity::collidesWith(Entity& other)
{
	if (!other.isCollidable()) return false;
	return this->boundingBox.checkCollision(other.boundingBox);
}

Hit* Entity::checkCollision(Entity& other)
{
	if (!other.isCollidable()) return nullptr;
	Hit* hit = this->boundingBox.checkIntersection(other.boundingBox);
	if (hit != nullptr) hit->tag = other.tag();
	return hit;
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_Rect location;
	location.x = position.x - (sprite->rect.w * 0.5f);
	location.y = position.y - (sprite->rect.h * 0.5f);
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	location.x /= scale.x;
	location.y /= scale.y;

	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);

	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
}

void Entity::renderColliders(SDL_Renderer* renderer)
{
	boundingBox.render(renderer);
}

void Entity::renderCollidersHit(SDL_Renderer* renderer)
{
	boundingBox.renderHit(renderer);
}

void entities::deleteAll(std::vector<Entity*>& entities)
{
	for (Entity* e : entities)
	{
		SafeDelete(e);
	}
	entities.clear();
}

void entities::updateEach(const std::vector<Entity*>& entities, float deltaTime)
{
	std::for_each(std::begin(entities), std::end(entities), [=](Entity* e) -> void { e->update(deltaTime); });
}

bool entities::containsOnly(const std::vector<Entity*>& entities, std::string tag)
{
	for (Entity* e : entities)
	{
		if (e->tag() != tag) return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////
// MEMORY LEAK CITY BELOW: TODO - FIX!
//////////////////////////////////////////////////////////////

void entities::removeDead(std::vector<Entity*>& entities)
{
	std::vector<Entity*>::iterator newEnd = std::partition(entities.begin(), entities.end(), [=](Entity* e) -> bool { return e->isAlive(); });
	entities.erase(newEnd, entities.end());
}

void entities::removeIfColliding(std::vector<Entity*>& entities, Entity* entity)
{
	std::vector<Entity*>::iterator newEnd = std::remove_if(entities.begin(), entities.end(), [=](Entity* e) -> bool { return e->collidesWith(*entity); });
	entities.erase(newEnd, entities.end());
}

void entities::renderAll(std::vector<Entity*>& entities, SDL_Renderer* renderer)
{
	for (Entity* e : entities)
	{
		e->render(renderer);
	}
}

void entities::checkAndNotifyCollisions(const std::vector<Entity*>& entities, Entity* entity, functions::Func* f)
{
	for (Entity* other : entities)
	{
		Hit* hit = entity->checkCollision(*other);
		if (hit != nullptr)
		{
			(*other).onCollision(hit);
			entity->onCollision(hit);
			SafeDelete(hit);

			if (f != nullptr)
			{
				(*f)();
			}
		}
	}
}

void entities::checkCollidesWithAndNotify(const std::vector<Entity*>& entities, Entity* entity, functions::Func1<Entity*>* f)
{
	for (Entity* other : entities)
	{
		if (other->collidesWith(*entity))
		{
			other->onCollision(nullptr);
			if (f != nullptr) (*f)(other);
		}
	}

}

void entities::checkCollidesWithAndEmptyNotify(const std::vector<Entity*>& entities, const std::vector<Entity*>& otherEntities)
{
	for (Entity* thisEntity : entities)
	{
		for (Entity* thatEntity : otherEntities)
		{
			if (thisEntity->collidesWith(*thatEntity))
			{
				thisEntity->onCollision(nullptr);
				thatEntity->onCollision(nullptr);
			}
		}
	}
}
