#include <iostream>
#include "Ball.h"

void Ball::setVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

void Ball::update(float deltaTime)
{
	float distanceX = velocity.x * deltaTime;
	float distanceY = velocity.y * deltaTime;

	position.x += distanceX;
	position.y += distanceY;

	std::cout << "Moving by: (" << distanceX << ", " << distanceY << ")" << std::endl;
	boundingBox.moveBy(distanceX, distanceY);
}