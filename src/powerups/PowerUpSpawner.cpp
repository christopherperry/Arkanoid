#include "PowerUpSpawner.h"
#include "ExpandCapsule.h"

PowerUpCapsule* PowerUpSpawner::spawn(SDL_Texture* texture, Vector2 position)
{
	return new ExpandCapsule(texture, position);
}
