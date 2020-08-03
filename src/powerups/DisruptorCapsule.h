#pragma once

#include <SDL.h>
#include <map>
#include "PowerUpCapsule.h"
#include "../sprites/Sprite.h"
#include "../AnimationFrames.h"

class DisruptorCapsule : public PowerUpCapsule
{
public:
	DisruptorCapsule(SDL_Texture* texture, Vector2 position);
	std::string tag() override { return "disruptor"; };
	PowerUp getPowerUp() override { return PowerUp::DISRUPTOR; }
};

