#include "Player.h"
#include "../utils/logger.h"

// TODO: update this when we have more states
AABB boxForState(PlayerState state, Vector2 position)
{
	return AABB{ position, Vector2{ 21.0f, 5.5f } };
}

Player::Player(SDL_Texture* texture, Vector2 position) : Entity(nullptr, AABB{ position, Vector2{ 21.0f, 5.5f } }, position)
{
	Vector2 extents{ 21.0f, 5.5f }; // Paddle size is 42 by 11
	AABB box{ position, extents };
	boundingBox = AABB{ position, extents };

	spriteRenderer = new PlayerSpriteRenderer(texture);
}

void Player::onEvent(SDL_Event event)
{
	switch (event.key.keysym.sym) {
	case SDLK_LEFT:
		movingLeft = event.type == SDL_KEYDOWN;
		break;
	case SDLK_RIGHT:
		movingRight = event.type == SDL_KEYDOWN;
		break;
	default:
		break;
	}
}

Vector2 Player::getPaddleTopCenterPosition()
{
	return Vector2(boundingBox.position.x, boundingBox.position.y - boundingBox.extents.y);
}

void Player::update(float deltaTime)
{
	if (isDissolving) // track render frames
	{
		if (totalAnimTimeMillis >= animationSpeed)
		{
			currentAnimFrame++;
			totalAnimTimeMillis = 0;
		}
		totalAnimTimeMillis += deltaTime;
	}
	else // allow movement
	{
		float directionX = 0;
		if (movingLeft)
		{
			directionX = -1;
		}
		else if (movingRight)
		{
			directionX = 1;
		}

		float distanceX = directionX * moveSpeed * deltaTime;
		position.x += distanceX;

		boundingBox.moveBy(distanceX, 0);
	}
}

void Player::onCollision(Hit* hit)
{
	// Move position out of collision
	position = position - hit->delta;
	boundingBox.moveBy(-hit->delta.x, -hit->delta.y);
}

void Player::render(SDL_Renderer* renderer)
{
	spriteRenderer->render(renderer, position);
}

void Player::dissolve()
{
	isDissolving = true;
}
