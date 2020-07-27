#pragma once

#include <map>
#include <SDL.h>
#include "sprites/sprite.h"
#include "math/Vector2.h"

class PlayerSpriteRenderer
{
private:
	std::map<int, Sprite*> sprites;
public:
	PlayerSpriteRenderer(SDL_Texture* texture);
	void render(SDL_Renderer* renderer, Vector2 position);
};

