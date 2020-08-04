#pragma once

#include "PowerUpCapsule.h"

class ShrinkCapsule : public PowerUpCapsule
{
public:
	ShrinkCapsule(SDL_Texture* texture, Vector2 position);
	std::string tag() const override { return "shrink"; };
	PowerUp getPowerUp() const { return PowerUp::SHRINK; }
};

