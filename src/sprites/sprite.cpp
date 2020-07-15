#pragma once

#include "sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect clip)
{
	this->renderer = renderer;
	this->spritesheet = spritesheet;
	this->clip = clip;
}

void Sprite::render(int x, int y)
{
	SDL_Rect location;
	location.x = x;
	location.y = y;
	location.w = clip.w;
	location.h = clip.h;

	//SDL_RenderCopy(renderer, spritesheet, NULL, NULL);
	SDL_RenderCopy(renderer, spritesheet, &clip, &location);
}