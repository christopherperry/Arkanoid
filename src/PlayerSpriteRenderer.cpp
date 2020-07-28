#include "PlayerSpriteRenderer.h"

enum PlayerSprites
{
	REG_LEFT,
	REG_RIGHT,
	REG_LEFT_DISSOLVE_1,
	REG_RIGHT_DISSOLVE_1,
	REG_LEFT_DISSOLVE_2,
	REG_RIGHT_DISSOLVE_2,
	REG_LEFT_DISSOLVE_3,
	REG_RIGHT_DISSOLVE_3,

	EXPANDED_LEFT,
	EXPANDED_RIGHT,

	GUNNER_LEFT,
	GUNNER_RIGHT,

	SHRUNK
};

const static int NO_OFFSET = 0;

void renderTwoSprite(SDL_Renderer* renderer, Sprite* leftHalf, Sprite* rightHalf, Vector2 position, int yOffset)
{
	SDL_Rect leftHalfLocation;
	leftHalfLocation.x = position.x - leftHalf->rect.w;
	leftHalfLocation.y = position.y - (leftHalf->rect.h * 0.5f) + yOffset;
	leftHalfLocation.w = leftHalf->rect.w;
	leftHalfLocation.h = leftHalf->rect.h;

	SDL_RenderCopy(renderer, leftHalf->texture, &leftHalf->rect, &leftHalfLocation);

	SDL_Rect rightHalfLocation;
	rightHalfLocation.x = position.x;
	rightHalfLocation.y = position.y - (rightHalf->rect.h * 0.5f) + yOffset;
	rightHalfLocation.w = rightHalf->rect.w;
	rightHalfLocation.h = rightHalf->rect.h;

	SDL_RenderCopy(renderer, rightHalf->texture, &rightHalf->rect, &rightHalfLocation);
}

void renderSingleSprite(SDL_Renderer* renderer, Sprite* sprite, Vector2 position)
{
	SDL_Rect location;
	location.x = position.x - (sprite->rect.w * 0.5f);
	location.y = position.y - (sprite->rect.h * 0.5f);
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}

PlayerSpriteRenderer::PlayerSpriteRenderer(SDL_Texture* texture)
{
	sprites = {
		{REG_LEFT, new Sprite{texture, SDL_Rect{235, 175, 21, 11}}},
		{REG_RIGHT, new Sprite{texture, SDL_Rect{257, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_1, new Sprite{texture, SDL_Rect{299, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_1, new Sprite{texture, SDL_Rect{321, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_2, new Sprite{texture, SDL_Rect{363, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_2, new Sprite{texture, SDL_Rect{385, 175, 21, 11}}},
		{REG_LEFT_DISSOLVE_3, new Sprite{texture, SDL_Rect{427, 175, 21, 11}}},
		{REG_RIGHT_DISSOLVE_3, new Sprite{texture, SDL_Rect{449, 175, 21, 11}}},

		{EXPANDED_LEFT, new Sprite{texture, SDL_Rect{261, 143, 27, 11}}},
		{EXPANDED_RIGHT, new Sprite{texture, SDL_Rect{289, 143, 27, 11}}},

		{GUNNER_LEFT, new Sprite{texture, SDL_Rect{330, 138, 22, 17}}},
		{GUNNER_RIGHT, new Sprite{texture, SDL_Rect{353, 138, 22, 17}}},

		{SHRUNK, new Sprite{texture, SDL_Rect{563, 239, 30, 11}}}
	};

	frames = new AnimationFrames(4, 150, false);
}

void PlayerSpriteRenderer::update(float deltaTimeMillis)
{
	if (renderMode == PlayerRenderMode::DISSOLVE)
	{
		frames->update(deltaTimeMillis);
	}
}

void PlayerSpriteRenderer::render(SDL_Renderer* renderer, Vector2 position)
{
	if (renderMode == PlayerRenderMode::REGULAR)
	{
		renderTwoSprite(renderer, sprites[REG_LEFT], sprites[REG_RIGHT], position, NO_OFFSET);
	}
	else if (renderMode == PlayerRenderMode::EXPANDED)
	{
		renderTwoSprite(renderer, sprites[EXPANDED_LEFT], sprites[EXPANDED_RIGHT], position, NO_OFFSET);
	}
	else if (renderMode == PlayerRenderMode::GUNNER)
	{
		renderTwoSprite(renderer, sprites[GUNNER_LEFT], sprites[GUNNER_RIGHT], position, -7);
	}
	else if (renderMode == PlayerRenderMode::SHRUNK)
	{
		renderSingleSprite(renderer, sprites[SHRUNK], position);
	}
	else if (renderMode == PlayerRenderMode::DISSOLVE)
	{
		int currentFrame = frames->getCurrentFrame();
		switch (currentFrame)
		{
		case 0:
			renderTwoSprite(renderer, sprites[REG_LEFT], sprites[REG_RIGHT], position, NO_OFFSET);
			break;
		case 1:
			renderTwoSprite(renderer, sprites[REG_LEFT_DISSOLVE_1], sprites[REG_RIGHT_DISSOLVE_1], position, NO_OFFSET);
			break;
		case 2:
			renderTwoSprite(renderer, sprites[REG_LEFT_DISSOLVE_2], sprites[REG_RIGHT_DISSOLVE_2], position, NO_OFFSET);
			break;
		case 3:
			renderTwoSprite(renderer, sprites[REG_LEFT_DISSOLVE_3], sprites[REG_RIGHT_DISSOLVE_3], position, NO_OFFSET);
			break;
		default:
			// don't render anything. 
			break;
		}
	}
}

void PlayerSpriteRenderer::setRenderMode(PlayerRenderMode renderMode)
{
	this->renderMode = renderMode;

	if (renderMode == PlayerRenderMode::DISSOLVE)
	{
		frames->startAnimation();
	}
}

bool PlayerSpriteRenderer::isAnimating()
{
	return !frames->isFinished();
}

void PlayerSpriteRenderer::resetAnimations()
{
	frames->reset();
}
