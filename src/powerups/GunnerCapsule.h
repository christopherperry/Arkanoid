#pragma once

#include "PowerUpCapsule.h"

class GunnerCapsule : public PowerUpCapsule
{
public:
	GunnerCapsule(SDL_Texture* texture, Vector2 position);
	std::string tag() const override { return "gun"; };
	PowerUp getPowerUp() const override { return PowerUp::GUN; }
};

