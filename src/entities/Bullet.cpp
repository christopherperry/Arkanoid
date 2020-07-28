#include "Bullet.h"

void Bullet::update(float deltaTimeMillis)
{
	// Always goes straight up
	position.y -= velocity.y * deltaTimeMillis;
	boundingBox.moveTo(position);
}
