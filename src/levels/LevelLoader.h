#pragma once

#include <map>
#include <vector>
#include <SDL.h>
#include "../sprites/sprite.h"
#include "../entities/Entity.h"
#include "LevelBrickLoader.h"

class LevelLoader
{
public:
	LevelLoader(SDL_Texture* texture);
	~LevelLoader();
	std::vector<Entity*> loadWallColliders(int level);
	std::vector<Entity*> loadNonColliders(int level);
	std::vector<Entity*> loadBricks(int level);
private:
	LevelBrickLoader* levelBrickLoader;
	std::map<int, Sprite*> sprites;
};

