#include "GameScreenManager.h"
#include "GameScreenTitle.h"
#include "GameScreenLevelOne.h"
#include "GameScreenGameOver.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = nullptr;

	ChangeScreen(startScreen);
}


GameScreenManager::~GameScreenManager()
{
	mRenderer = nullptr;

	delete mCurrentScreen;
	mCurrentScreen = nullptr;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	// check if screen needs to be changed
	if (mCurrentScreen->GetState() == GAMEOVER)
	{
		switch (mCurrentScreenType) // can't directly check screen class, so save as separate var
		{
		case SCREEN_MENU:
			ChangeScreen(SCREEN_PLAY);
			break;
		case SCREEN_PLAY:
			ChangeScreen(SCREEN_GAMEOVER);
			break;
		case SCREEN_GAMEOVER:
			ChangeScreen(SCREEN_MENU);
			break;
		}
	}

	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen != nullptr)
	{
		delete mCurrentScreen;
	}

	mCurrentScreenType = newScreen;

	switch (newScreen)
	{
	case SCREEN_MENU:
		mCurrentScreen = (GameScreen*)(new GameScreenTitle(mRenderer));
		break;
	case SCREEN_PLAY:
		mCurrentScreen = (GameScreen*)(new GameScreenLevelOne(mRenderer));
		break;
	case SCREEN_GAMEOVER:
		mCurrentScreen = (GameScreen*)(new GameScreenGameOver(mRenderer));
		break;
	}
}
