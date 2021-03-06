#pragma once

#include <map>
#include <SDL.h>
#include "sprites/Sprite.h"
#include "math/Vector2.h"
#include "AnimationFrames.h"

enum class PlayerRenderMode
{
	REGULAR,
	DISSOLVE,
	EXPANDED,
	GUNNER,
	SHRUNK
};

class PlayerSpriteRenderer
{
private:
	Vector2 scale{ 1.5f, 1.5f };
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

