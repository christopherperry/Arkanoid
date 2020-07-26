#include "Text.h"

Text::Text(SDL_Renderer* renderer, TTF_Font* font, std::string textString, SDL_Color textColor)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textString.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	width = textSurface->w;
	height = textSurface->h;
}