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
};

void renderTwoSprite(SDL_Renderer* renderer, Sprite* leftHalf, Sprite* rightHalf, Vector2 position)
{
	SDL_Rect leftHalfLocation;
	leftHalfLocation.x = position.x - leftHalf->rect.w;
	leftHalfLocation.y = position.y - (leftHalf->rect.h * 0.5f);
	leftHalfLocation.w = leftHalf->rect.w;
	leftHalfLocation.h = leftHalf->rect.h;

	SDL_RenderCopy(renderer, leftHalf->texture, &leftHalf->rect, &leftHalfLocation);

	SDL_Rect rightHalfLocation;
	rightHalfLocation.x = position.x;
	rightHalfLocation.y = position.y - (rightHalf->rect.h * 0.5f);
	rightHalfLocation.w = rightHalf->rect.w;
	rightHalfLocation.h = rightHalf->rect.h;

	SDL_RenderCopy(renderer, rightHalf->texture, &rightHalf->rect, &rightHalfLocation);
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
	};
}

void PlayerSpriteRenderer::render(SDL_Renderer* renderer, Vector2 position)
{
	renderTwoSprite(renderer, sprites[REG_LEFT], sprites[REG_RIGHT], position);
}
