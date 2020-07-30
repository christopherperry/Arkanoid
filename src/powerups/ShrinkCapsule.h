#pragma once

#include "PowerUpCapsule.h"

class ShrinkCapsule : public PowerUpCapsule
{
public:
	ShrinkCapsule(SDL_Texture* texture, Vector2 position);
	std::string tag() override { return "shrink"; };
	PowerUp getPowerUp() { return PowerUp::SHRINK; }
};

