#pragma once

#include <map>
#include <vector>
#include <SDL.h>
#include "sprites/sprite.h"
#include "Entity.h"

class LevelLoader
{
public:
	LevelLoader(SDL_Texture* texture);
	~LevelLoader();
	std::vector<Entity*> loadLevel(int level);
private:
	std::map<int, Sprite*> sprites;
};

