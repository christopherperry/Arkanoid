#include "TextRenderer.h"

void TextRenderer::render(SDL_Renderer* renderer, Text* text, SDL_Rect location)
{
	SDL_Rect textureRect;
	textureRect.x = 0;
	textureRect.y = 0;
	textureRect.w = text->width;
	textureRect.h = text->height;

	SDL_RenderCopy(renderer, text->texture, &textureRect, &location);
}
