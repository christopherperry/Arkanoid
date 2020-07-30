#include <SDL.h>
#include <assert.h>
#include "PowerUpSpawner.h"
#include "ExpandCapsule.h"
#include "GunnerCapsule.h"
#include "ShrinkCapsule.h"

PowerUpCapsule* randomPowerUp(SDL_Texture* texture, Vector2 position)
{
	int v = (rand() % 100) + 1; // between 1 and 100
	assert(v >= 1 && v <= 100);

	if (v <= 10) // 10%
	{
		// If you get this it's just bad luck
		return new ShrinkCapsule(texture, position);
	}
	else if (v <= 55) // 45%
	{
		return new GunnerCapsule(texture, position);
	}
	else // 45%
	{
		return new ExpandCapsule(texture, position);
	}
}

PowerUpSpawner::PowerUpSpawner()
{
	// Seed the RNG
	srand(SDL_GetTicks());
}

PowerUpCapsule* PowerUpSpawner::spawn(SDL_Texture* texture, Vector2 position)
{
	int v = (rand() % 100) + 1; // between 1 and 100
	assert(v >= 1 && v <= 100);

	// 15% chance to get a power up
	if (v <= 15)
	{
		return randomPowerUp(texture, position);
	}

	return nullptr;
}
