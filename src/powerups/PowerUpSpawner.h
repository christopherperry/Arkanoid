#pragma once

#include "PowerUpCapsule.h"
#include "../math/Vector2.h"

class PowerUpSpawner
{
public:
	PowerUpSpawner();
	PowerUpCapsule* spawn(SDL_Texture* texture, Vector2 position);
};

