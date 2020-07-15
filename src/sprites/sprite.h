#pragma once

#include <SDL.h>

class Sprite
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;
	SDL_Rect clip;
public:
	Sprite(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect clip);
	void render(int x, int y);
};