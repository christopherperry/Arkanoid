#include <iostream>
#include "Ball.h"
#include "../math/Vector2.h"
#include "../Constants.h"
#include "../Sounds.h"

Ball* Ball::createNew(SDL_Texture* texture, Vector2 position, Mix_Chunk* hitBrickSound, Mix_Chunk* hitUnbreakableBrickSound, Mix_Chunk* hitPaddleSound)
{
	Vector2 scale{ 1.5f, 1.5f };
	Vector2 ballExtents{ Constants::BALL_SIZE  * 0.5f * scale.x, Constants::BALL_SIZE * 0.5f * scale.y };

	return new Ball(
		new Sprite{ texture, {463, 142, 6, 6} },
		AABB{ position, ballExtents },
		position,
		scale,
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

std::vector<Entity*> Ball::disrupt()
{
	// Seed the RNG
	srand(SDL_GetTicks());

	float pi = 2 * std::acos(0);
	int randomAngleDegrees = (rand() % 180) + 1; // between 1 and 180
	float randomAngleRadians = randomAngleDegrees * (pi / 180.0f);

	Ball* ballCopyOne = new Ball(*this);
	ballCopyOne->velocity = velocity.rotated(randomAngleRadians);

	randomAngleDegrees = (rand() % 180) + 1; // between 1 and 180
	randomAngleRadians = randomAngleDegrees * (pi / 180.0f);

	Ball* ballCopyTwo = new Ball(*this);
	ballCopyTwo->velocity = velocity.rotated(randomAngleRadians);

	// Make sure they're both pointing up
	ballCopyOne->velocity.y = abs(ballCopyOne->velocity.y) * -1.0f;
	ballCopyTwo->velocity.y = abs(ballCopyOne->velocity.y) * -1.0f;

	return std::vector<Entity*>{ ballCopyOne, ballCopyTwo };
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
	else if (tag == "unbreakable-brick" || tag == "grey-brick")
	{
		Sounds::play(hitUnbreakableBrickSound);
	}

	// We need to first move the ball to not be in a colliding state
	position = position - hit->delta;
	boundingBox.moveBy(-hit->delta.x, -hit->delta.y);

	////////////////////////////////////////////////
	// Ball Velocity Change
	////////////////////////////////////////////////

	// If the ball hit the side of the paddle we just reverse the velocity so
	// the ball doesn't reflect off the side and we lose it immediately (not fun gameplay)
	if (tag == "player" && abs(hit->normal.x) == 1.0f)
	{
		std::cout << "Ball hit paddle side, reversing the velocity..." << std::endl;
		velocity = -velocity;
	}
	else
	{
		// Else we mirror the current velocity around the collision normal using some 3D math.
		// ReflectedVelocity = CurrentVelocity - 2 (CurrentVelocity dot hitnormal) hitnormal
		Vector2 normal = -hit->normal;
		float dotNormal = velocity.dot(normal);
		Vector2 reflectedVelocity = velocity - (normal * (2.0f * dotNormal));

		std::cout << "Velocity = (" << velocity.x << ", " << velocity.y << ")" << std::endl;
		std::cout << "Reflected Velocity = (" << reflectedVelocity.x << ", " << reflectedVelocity.y << ")" << std::endl;

		velocity = reflectedVelocity;

		// Adjust the velocity if the thing we hit was moving
		if (abs(hit->velocity.x) > 0.0f)
		{
			std::cout << "Adjusting ball velocity, the thing we hit was moving" << std::endl;
			if (hit->velocity.x < 0.0f) // moving left
			{
				velocity.x = velocity.x * (velocity.x > 0.0f ? 0.6f : 1.08f);
			}
			else // moving right
			{
				velocity.x = velocity.x * (velocity.x < 0.0f ? 0.6f : 1.08f);
			}
		}
	}
}
