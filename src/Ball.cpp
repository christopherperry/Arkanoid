#include <iostream>
#include "Ball.h"
#include "Vector2.h"

void Ball::setVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

void Ball::movePosition(Vector2 position)
{
	this->position = position;
	boundingBox.moveTo(position);
}

void Ball::update(float deltaTime)
{
	float distanceX = velocity.x * deltaTime;
	float distanceY = velocity.y * deltaTime;

	position.x += distanceX;
	position.y += distanceY;

	boundingBox.moveBy(distanceX, distanceY);
}

void Ball::onCollision(Hit* hit)
{
	std::cout << "HIT! = (" << hit->normal.x << ", " << hit->normal.y << ")" << std::endl;
	std::string tag = hit->tag;
	if (tag == "player")
	{
		Mix_PlayChannel(-1, hitPaddleSound, 0);
	}
	else if (tag == "brick")
	{
		Mix_PlayChannel(-1, hitBrickSound, 0);
	}

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
