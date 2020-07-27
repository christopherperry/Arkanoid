#include "PowerUpCapsule.h"

PowerUpCapsule::PowerUpCapsule(Vector2 position) : Entity(nullptr, AABB{ position, Vector2{ 11.5f, 5.5f } }, position)
{
	animationFrames.startAnimation();
}

void PowerUpCapsule::update(float deltaTimeMillis)
{
	position.y += velocity.y * deltaTimeMillis;
	boundingBox.moveTo(position);
	animationFrames.update(deltaTimeMillis);
}
