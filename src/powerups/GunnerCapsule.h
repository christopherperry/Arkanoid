#pragma once

#include "PowerUpCapsule.h"

class GunnerCapsule : public PowerUpCapsule
{
public:
	GunnerCapsule(SDL_Texture* texture, Vector2 position);
	PowerUp getPowerUp() override { return PowerUp::GUN; }
};

