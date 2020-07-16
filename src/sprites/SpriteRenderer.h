#pragma once
#include "spritesheet.h"

class SpriteRenderer
{
private: 
	SDL_Renderer* renderer;
public:
	SpriteRenderer(SDL_Renderer* renderer);
	void render(const Spritesheet& spritesheet, int spriteId, int locationX, int locationY);
};

