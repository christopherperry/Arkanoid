#include "Entity.h"

bool Entity::collidesWith(Entity& other)
{
	if (!other.isCollidable()) return false;
	return this->boundingBox.checkCollision(other.boundingBox);
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
