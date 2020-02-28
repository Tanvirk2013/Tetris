#include "AudioManager.h"



AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}

void AudioManager::PlaySound(Mix_Chunk* soundFX)
{
	Mix_PlayChannel(-1, soundFX, 0);
}

void AudioManager::PlayMusic(std::string path)
{
	Mix_Music* music = Mix_LoadMUS(path.c_str());
	if (!(music == nullptr))
		Mix_PlayMusic(music, -1);
}

void AudioManager::ToggleMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}

}
