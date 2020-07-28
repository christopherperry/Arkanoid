#pragma once

#include "PowerUpCapsule.h"

class ShrinkCapsule : public PowerUpCapsule
{
public:
	ShrinkCapsule(SDL_Texture* texture, Vector2 position);
	PowerUp getPowerUp() { return PowerUp::SHRINK; }
};

