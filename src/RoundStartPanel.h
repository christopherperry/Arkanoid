#pragma once

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"

class RoundStartPanel
{
public:
	RoundStartPanel(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect);
	void render(SDL_Renderer* renderer, int roundNumber);
private:
	std::map<int, Text*> text;
	SDL_Rect panelRect;
};

