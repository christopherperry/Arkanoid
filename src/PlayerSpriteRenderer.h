#pragma once

#include <map>
#include <SDL.h>
#include "sprites/sprite.h"
#include "math/Vector2.h"
#include "AnimationFrames.h"

class PlayerSpriteRenderer
{
private:
	std::map<int, Sprite*> sprites;
	AnimationFrames* frames;
public:
	PlayerSpriteRenderer(SDL_Texture* texture);
	void update(float deltaTimeMillis);
	void render(SDL_Renderer* renderer, Vector2 position);
	void startAnimation();
	bool isAnimating();
	void resetAnimations();
};

