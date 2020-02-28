#pragma once

#include <SDL.h>
#include "Commons.h"
#include "Texture2D.h"

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e) = 0;

	SCREEN_STATE GetState() { return mState; }

protected:
	SDL_Renderer* mRenderer;
	Texture2D* mBackgroundTexture;

	SCREEN_STATE mState;
};

