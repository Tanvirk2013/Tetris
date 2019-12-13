#include "GameScreen.h"


GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mState = RUNNING;
}

GameScreen::~GameScreen()
{
	mRenderer = nullptr;

	delete mBackgroundTexture;
	mBackgroundTexture = nullptr;
}