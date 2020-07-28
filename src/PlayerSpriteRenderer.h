#pragma once

#include <map>
#include <SDL.h>
#include "sprites/sprite.h"
#include "math/Vector2.h"
#include "AnimationFrames.h"

enum class PlayerRenderMode
{
	REGULAR,
	DISSOLVE,
	EXPANDED,
	GUNNER
};

class PlayerSpriteRenderer
{
private:
	std::map<int, Sprite*> sprites;
	AnimationFrames* frames;
	PlayerRenderMode renderMode{ PlayerRenderMode::REGULAR };
public:
	PlayerSpriteRenderer(SDL_Texture* texture);
	void update(float deltaTimeMillis);
	void render(SDL_Renderer* renderer, Vector2 position);
	void setRenderMode(PlayerRenderMode renderMode);
	bool isAnimating();
	void resetAnimations();
};

