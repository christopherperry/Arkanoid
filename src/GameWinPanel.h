#pragma once

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"
#include "sprites/Sprite.h"

class GameWinPanel
{
public:
	GameWinPanel(SDL_Texture* texture, SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect);
	void render(SDL_Renderer* renderer);
private:
	std::map<int, Text*> text;
	std::map<int, Sprite*> sprites;
	SDL_Rect panelRect;
};