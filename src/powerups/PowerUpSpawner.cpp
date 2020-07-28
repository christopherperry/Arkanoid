#include "PowerUpSpawner.h"
#include "ExpandCapsule.h"
#include "GunnerCapsule.h"

PowerUpCapsule* PowerUpSpawner::spawn(SDL_Texture* texture, Vector2 position)
{
	return new GunnerCapsule(texture, position);
}
