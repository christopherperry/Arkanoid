#pragma once

#include <SDL.h>
#include <map>
#include "PowerUpCapsule.h"
#include "../sprites/Sprite.h"
#include "../AnimationFrames.h"

class ExpandCapsule : public PowerUpCapsule
{
public:
	ExpandCapsule(SDL_Texture* texture, Vector2 position);
	std::string tag() const override { return "expand"; };
	PowerUp getPowerUp() const override { return PowerUp::EXPAND; }
};