#pragma once

#include <SDL.h>
#include <map>
#include "PowerUpCapsule.h"
#include "../sprites/sprite.h"
#include "../AnimationFrames.h"

class ExpandCapsule : public PowerUpCapsule
{
private:
	std::map<int, Sprite*> sprites;
public:
	ExpandCapsule(SDL_Texture* texture, Vector2 position);
	~ExpandCapsule();
	void render(SDL_Renderer* renderer) override;
	PowerUp getPowerUp() override { return PowerUp::EXPAND; }
};

