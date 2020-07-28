#include "BulletSpawner.h"

BulletSpawner::BulletSpawner(SDL_Texture* texture)
{
	bulletSprite = new Sprite{ texture, SDL_Rect{398, 141, 5, 11} };
	lastSpawnTime = SDL_GetTicks();
}

std::pair<Bullet*, Bullet*> BulletSpawner::spawn(Vector2 position)
{
	// 19 offset on the x
	// 11 offset on the y
	// I may need to play with these to get it right

	Vector2 leftPosition{ position.x - 19, position.y - 11 };
	Vector2 rightPosition{ position.x + 19, position.y - 11 };

	Vector2 extents{ 2.5f, 5.5f };

	Bullet* leftBullet = new Bullet{ bulletSprite, AABB{leftPosition, extents}, leftPosition };
	Bullet* rightBullet = new Bullet{ bulletSprite, AABB{rightPosition, extents}, rightPosition };

	lastSpawnTime = SDL_GetTicks();

	return std::pair<Bullet*, Bullet*>(leftBullet, rightBullet);
}

bool BulletSpawner::canSpawn()
{
	float currentTime = SDL_GetTicks();
	return (currentTime - lastSpawnTime) >= timeUntilSpawn;
}
