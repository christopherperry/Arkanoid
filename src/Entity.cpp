#include "Entity.h"

Entity::Entity(Sprite* sprite, BoundingBox boundingBox, int spriteId, int positionX, int positionY, bool moveable)
{
	this->boundingBox = boundingBox;
	this->sprite = sprite;
	this->positionX = positionX;
	this->positionY = positionY;
	this->moveable = moveable;
}

void Entity::move(int x, int y)
{
	if (!moveable) return;
	this->positionX = x;
	this->positionY = y;
	this->boundingBox.moveTo(x, y);
}

bool Entity::collidesWith(Entity& other)
{
	return this->boundingBox.collidesWith(other.boundingBox);
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_Rect location;
	location.x = positionX;
	location.y = positionY;
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}
