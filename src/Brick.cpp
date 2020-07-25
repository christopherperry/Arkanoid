#include <iostream>
#include "Brick.h"

void Brick::onCollision(Hit* hit)
{
	std::cout << "HIT BRICK!!!" << std::endl;
	totalHits++;
}

bool Brick::isAlive()
{
	return totalHits < numHitsToDestroy;
}
