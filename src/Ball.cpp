#include <iostream>
#include "Ball.h"
#include "Vector2.h"

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

	boundingBox.moveBy(distanceX, distanceY);
}

void Ball::onCollision(Hit* hit, float deltaTime)
{
	std::cout << "HIT! = (" << hit->normal.x << ", " << hit->normal.y << ")" << std::endl;

	// We need to first move the ball to not be in a colliding state
	position = position - hit->delta;
	boundingBox.moveBy(-hit->delta.x, -hit->delta.y);

	// Next we change the velocity of the ball to mirror the current velocity
	// ReflectedVelocity = CurrentVelocity - 2 (CurrentVelocity dot hitnormal) hitnormal
	Vector2 normal = -hit->normal;
	float dotNormal = velocity.dot(normal);
	Vector2 reflectedVelocity = velocity - (normal * (2 * dotNormal));

	std::cout << "V = (" << velocity.x << ", " << velocity.y << ")" << std::endl;
	std::cout << "VR = (" << reflectedVelocity.x << ", " << reflectedVelocity.y << ")" << std::endl;

	velocity = reflectedVelocity;
}
