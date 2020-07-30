#pragma once

#include <SDL_mixer.h>

class Sounds
{
public:
	static void play(Mix_Chunk* sound);
	static void play(Mix_Music* music);
};

