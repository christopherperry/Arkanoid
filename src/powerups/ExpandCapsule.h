#pragma once

#include <SDL.h>
#include <map>
#include "PowerUpCapsule.h"
#include "../sprites/sprite.h"
#include "../AnimationFrames.h"

class ExpandCapsule : public PowerUpCapsule
{
public:
	ExpandCapsule(SDL_Texture* texture, Vector2 position);
	PowerUp getPowerUp() override { return PowerUp::EXPAND; }
};

