#pragma once

#include "GameScreen.h"
#include <SDL.h>
#include "Commons.h"

class Texture2D;

class GameScreenTitle : GameScreen
{
public:
	GameScreenTitle(SDL_Renderer* renderer);
	~GameScreenTitle();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
};

