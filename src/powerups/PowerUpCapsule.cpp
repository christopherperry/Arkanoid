#include "PowerUpCapsule.h"
#include "../utils/Util.h"

PowerUpCapsule::PowerUpCapsule(Vector2 position) : Entity(nullptr, AABB{ position, Vector2{ 11.5f, 5.5f } }, position)
{
	animationFrames.startAnimation();
}

PowerUpCapsule::~PowerUpCapsule()
{
	for (auto const&[_, sprite] : sprites)
	{
		SafeDelete(sprite);
	}
}

void PowerUpCapsule::update(float deltaTimeMillis)
{
	position.y += velocity.y * deltaTimeMillis;
	boundingBox.moveTo(position);
	animationFrames.update(deltaTimeMillis);
}

void PowerUpCapsule::render(SDL_Renderer* renderer) const
{
	int frameNumber = animationFrames.getCurrentFrame();
	Sprite* sprite = sprites.at(frameNumber);

	SDL_Rect location;
	location.x = position.x - (sprite->rect.w * 0.5f);
	location.y = position.y - (sprite->rect.h * 0.5f);
	location.w = sprite->rect.w;
	location.h = sprite->rect.h;

	SDL_RenderCopy(renderer, sprite->texture, &sprite->rect, &location);
}

void PowerUpCapsule::onCollision(Hit* hit)
{
	numHits++;
}

bool PowerUpCapsule::isAlive() const
{
	return numHits == 0;
}
