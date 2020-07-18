#include "Entity.h"

Entity::Entity(Sprite* sprite, BoundingBox boundingBox, SDL_Point position)
{
	this->boundingBox = boundingBox;
	this->sprite = sprite;
	this->position = position;
}

bool Entity::collidesWith(Entity& other)
{
	return this->boundingBox.collidesWith(other.boundingBox);
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_Rect location;
	location.x = position.x;
	location.y = position.y;
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	boundingBox.render(renderer);

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}
