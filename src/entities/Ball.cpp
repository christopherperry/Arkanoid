#include <iostream>
#include "Ball.h"
#include "../math/Vector2.h"
#include "../Constants.h"
#include "../Sounds.h"

Ball* Ball::createNew(SDL_Texture* texture, Vector2 position, Mix_Chunk* hitBrickSound, Mix_Chunk* hitUnbreakableBrickSound, Mix_Chunk* hitPaddleSound)
{
	Vector2 ballExtents{ Constants::BALL_SIZE  * 0.5f, Constants::BALL_SIZE  * 0.5f };

	return new Ball(
		new Sprite{ texture, {463, 142, 6, 6} },
		AABB{ position, ballExtents },
		position,
		hitBrickSound,
		hitUnbreakableBrickSound,
		hitPaddleSound
	);
}

void Ball::launch()
{
	float pi = 2 * std::acos(0);
	float angleRadians = 45.0f * (pi / 180.0f);
	Vector2 startVelocity = Vector2(std::cos(angleRadians), -std::sin(angleRadians)) * Constants::BALL_SPEED;

	this->velocity = startVelocity;
}

void Ball::increaseSpeed()
{
	// Increases until max velocity, then maintains that velocity.
	velocity += velocity * 0.1f * (1.0f - velocity.squareMagnitude() / Constants::BALL_SPEED_MAX_SQUARED);
}

void Ball::reset(Vector2 position)
{
	this->velocity = Vector2::zero;
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
		Sounds::play(hitPaddleSound);
	}
	else if (tag == "brick")
	{
		Sounds::play(hitBrickSound);
	}
	else if (tag == "unbreakable-brick")
	{
		Sounds::play(hitUnbreakableBrickSound);
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
