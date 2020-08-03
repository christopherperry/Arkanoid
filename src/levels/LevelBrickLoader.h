#pragma once
#include <map>
#include <vector>
#include <SDL.h>
#include "../sprites/Sprite.h"
#include "../entities/Entity.h"

class LevelBrickLoader
{
public:
	LevelBrickLoader(SDL_Texture* texture);
	LevelBrickLoader(const LevelBrickLoader&) = delete;
	LevelBrickLoader& operator=(const LevelBrickLoader&) = delete;
	~LevelBrickLoader();
	std::vector<Entity*> loadLevel(int level);
private:
	static const int BRICK_WIDTH = 31;
	static const int BRICK_HEIGHT = 16;
	std::map<int, Sprite*> sprites;
};

