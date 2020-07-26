#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"
#include "Vector2.h"

class Text
{
	friend class TextRenderer;

public:
	Text(SDL_Renderer* renderer, TTF_Font* font, std::string textString, SDL_Color textColor);
	int getWidth() { return width; }
	int getHeight() { return height; }
private:
	int width{ 0 }, height{ 0 };
	SDL_Texture* texture;
};

