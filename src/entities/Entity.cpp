#include "Entity.h"

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

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}

void Entity::renderColliders(SDL_Renderer* renderer)
{
	boundingBox.render(renderer);
}

void Entity::renderCollidersHit(SDL_Renderer* renderer)
{
	boundingBox.renderHit(renderer);
}

void entities::updateEach(const std::vector<Entity*>& entities, float deltaTime)
{
	std::for_each(std::begin(entities), std::end(entities), [=](Entity* e) -> void { e->update(deltaTime); });
}

void entities::removeDead(std::vector<Entity*>& entities)
{
	std::vector<Entity*>::iterator newEnd = std::partition(entities.begin(), entities.end(), [=](Entity* e) -> bool { return e->isAlive(); });
	entities.erase(newEnd, entities.end());
}
