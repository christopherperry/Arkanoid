#pragma once

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "math/Vector2.h"
#include "Text.h"

class ScoresPanel
{
private:
	std::map<int, Text*> text;
	Vector2 position;
public:
	ScoresPanel(SDL_Renderer* renderer, TTF_Font* font, Vector2 position);
	void render(SDL_Renderer* renderer, int totalLives, int currentScore);
};