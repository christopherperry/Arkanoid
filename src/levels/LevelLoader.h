#pragma once

#include <map>
#include <vector>
#include <SDL.h>
#include "../sprites/Sprite.h"
#include "../entities/Entity.h"
#include "LevelBrickLoader.h"

class LevelLoader
{
public:
	LevelLoader(SDL_Texture* texture);
	LevelLoader& operator=(const LevelLoader&) = delete;
	LevelLoader(const LevelLoader&) = delete;
	~LevelLoader();
	std::vector<Entity*> loadWallColliders(int level) const;
	std::vector<Entity*> loadNonColliders(int level) const;
	std::vector<Entity*> loadBricks(int level) const;
private:
	LevelBrickLoader* levelBrickLoader;
	std::map<int, Sprite*> sprites;
};

