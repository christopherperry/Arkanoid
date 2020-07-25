#include <iostream>
#include "Brick.h"

void Brick::onCollision(Hit* hit)
{
	totalHits++;
}

bool Brick::isAlive()
{
	return totalHits < numHitsToDestroy;
}
