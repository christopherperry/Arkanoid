#include "Entity.h"

bool Entity::collidesWith(Entity& other)
{
	return this->boundingBox.checkCollision(other.boundingBox);
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_Rect location;
	location.x = position.x;
	location.y = position.y;
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}

void Entity::renderColliders(SDL_Renderer* renderer)
{
	boundingBox.render(renderer);
}
