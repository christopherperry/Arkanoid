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
	std::string tag() const override { return "disruptor"; };
	PowerUp getPowerUp() const override { return PowerUp::DISRUPTOR; }
};

