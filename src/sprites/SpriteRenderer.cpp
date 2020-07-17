#include "SpriteRenderer.h"
#include "spritesheet.h"

SpriteRenderer::SpriteRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void SpriteRenderer::render(const Spritesheet& spritesheet, int spriteId, int locationX, int locationY)
{
	Sprite sprite = spritesheet.sprites.at(spriteId);
	SDL_Rect location;
	location.x = (locationX - (sprite.rect.w / 2.0));
	location.y = (locationY - (sprite.rect.h / 2.0));
	location.w = sprite.rect.w;
	location.h = sprite.rect.h;

	SDL_RenderCopy(renderer, spritesheet.texture, &sprite.rect, &location);
}