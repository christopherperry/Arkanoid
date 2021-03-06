#pragma once

#include <SDL.h>
#include "Text.h"
#include "math/Vector2.h"

class TextRenderer
{
public:
	static void render(SDL_Renderer* renderer, Text* text, SDL_Rect location);
};

