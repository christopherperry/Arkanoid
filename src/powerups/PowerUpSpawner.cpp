#include "PowerUpSpawner.h"
#include "ExpandCapsule.h"
#include "GunnerCapsule.h"
#include "ShrinkCapsule.h"

PowerUpCapsule* PowerUpSpawner::spawn(SDL_Texture* texture, Vector2 position)
{
	return new ShrinkCapsule(texture, position);
}
