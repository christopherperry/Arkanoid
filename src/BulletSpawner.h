#pragma once

#include <SDL.h>
#include <utility>
#include "entities/Bullet.h"

class BulletSpawner
{
private:
	Sprite* bulletSprite;
	float lastSpawnTime;
	float timeUntilSpawn{ 200 };
public:
	BulletSpawner(SDL_Texture* texture);

	// This is meant to be the player's position that you pass
	std::pair<Bullet*, Bullet*> spawn(Vector2 position);

	bool canSpawn();
};

