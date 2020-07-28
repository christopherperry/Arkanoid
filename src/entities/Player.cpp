#include "Player.h"
#include "../utils/logger.h"
#include "../Constants.h"

// TODO: update this when we have more states
AABB boxForState(PlayerState state, Vector2 position)
{
	if (state == PlayerState::EXPANDED)
	{
		return AABB{ position, Vector2{ 27.0f, 5.5f } };
	}
	else if (state == PlayerState::SHRUNK)
	{
		return AABB{ position, Vector2{ 15.0f, 5.5f } };
	}

	// Default to regular size
	return AABB{ position, Vector2{ 21.0f, 5.5f } };
}

Player* Player::createNew(SDL_Texture * texture)
{
	int positionX = (Constants::NUM_TILES_WIDE * Constants::TILE_SIZE * 0.5f);
	int positionY = (Constants::NUM_TILES_HIGH - 2) * Constants::TILE_SIZE;
	Vector2 position = Vector2(positionX, positionY);

	return new Player(texture, position);
}

Player::Player(SDL_Texture* texture, Vector2 position) : Entity(nullptr, AABB{ position, Vector2{ 21.0f, 5.5f } }, position), startPosition{position}
{
	boundingBox = boxForState(state, position);
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

	float distanceX = directionX * moveSpeed * deltaTime;
	position.x += distanceX;

	boundingBox.moveBy(distanceX, 0);
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

void Player::setState(PlayerState state)
{
	this->state = state;
	this->boundingBox = boxForState(state, position);

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
	boundingBox = boxForState(state, position);
	boundingBox.moveTo(position);

	spriteRenderer->setRenderMode(PlayerRenderMode::REGULAR);
	spriteRenderer->resetAnimations();
}
