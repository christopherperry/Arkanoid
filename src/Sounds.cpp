#include "Sounds.h"

void Sounds::play(Mix_Chunk* sound)
{
	Mix_PlayChannel(-1, sound, 0);
}

void Sounds::play(Mix_Music* music)
{
	Mix_PlayMusic(music, 0);
}
