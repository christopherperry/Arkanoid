#include "Player.h"
#include "../utils/logger.h"
#include "../Constants.h"

// TODO: update this when we have more states
AABB boxForState(PlayerState state, Vector2 position, Vector2 scale)
{
	if (state == PlayerState::EXPANDED)
	{
		return AABB{ position, Vector2{ scale.x * 27.0f, scale.y * 5.5f } };
	}
	else if (state == PlayerState::SHRUNK)
	{
		return AABB{ position, Vector2{ scale.x * 15.0f, scale.y * 5.5f } };
	}

	// Default to regular size
	return AABB{ position, Vector2{ scale.x * 21.0f, scale.y * 5.5f } };
}

Player* Player::createNew(SDL_Texture * texture)
{
	int positionX = (Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f);
	int positionY = (Constants::NUM_TILES_HIGH - 2) * Constants::TILE_SIZE;
	Vector2 position = Vector2(positionX, positionY);

	return new Player(texture, position, Vector2{ 1.5f, 1.5f });
}

Player::Player(SDL_Texture* texture, Vector2 position, Vector2 scale) : Entity(nullptr, AABB{ position, Vector2{ 21.0f, 5.5f } }, position, scale), startPosition{position}
{
	boundingBox = boxForState(state, position, scale);
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

Vector2 Player::getVelocity()
{
	return velocity;
}

void Player::update(float deltaTime)
{
	spriteRenderer->update(deltaTime);

	float directionX = 0;
	if (movingLeft)
	{
		directionX = -1;
	}
	else if (movingRight)
	{
		directionX = 1;
	}

	velocity = Vector2(directionX * moveSpeed * deltaTime, 0.0f);
	position.x += velocity.x;

	boundingBox.moveBy(velocity.x, 0);
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
	boundingBox.render(renderer);
}

void Player::setState(PlayerState state)
{
	this->state = state;
	this->boundingBox = boxForState(state, position, scale);

	if (state == PlayerState::REGULAR)
	{
		spriteRenderer->setRenderMode(PlayerRenderMode::REGULAR);
	}
	else if (state == PlayerState::DISSOLVE)
	{
		movingLeft = false;
		movingRight = false;
		spriteRenderer->setRenderMode(PlayerRenderMode::DISSOLVE);
	}
	else if (state == PlayerState::EXPANDED)
	{
		spriteRenderer->setRenderMode(PlayerRenderMode::EXPANDED);
	}
	else if (state == PlayerState::GUNNER)
	{
		spriteRenderer->setRenderMode(PlayerRenderMode::GUNNER);
	}
	else if (state == PlayerState::SHRUNK)
	{
		spriteRenderer->setRenderMode(PlayerRenderMode::SHRUNK);
	}
}

PlayerState Player::getState()
{
	return state;
}

bool Player::isReadyToLaunch()
{
	return !spriteRenderer->isAnimating();
}

void Player::reset()
{
	position = startPosition;
	state = PlayerState::REGULAR;
	boundingBox = boxForState(state, position, scale);
	boundingBox.moveTo(position);

	spriteRenderer->setRenderMode(PlayerRenderMode::REGULAR);
	spriteRenderer->resetAnimations();
}
