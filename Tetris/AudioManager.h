#pragma once

#include "Commons.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySound(Mix_Chunk* soundFX);
	void PlayMusic(std::string path);
	void ToggleMusic();

};

