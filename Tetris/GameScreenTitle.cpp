#include "GameScreenTitle.h"
#include <iostream>
#include "Texture2D.h"

GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenTitle::~GameScreenTitle()
{
	// inherits background texture deletion from GameScreen
}

void GameScreenTitle::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, 0.0);
	// TODO text/buttons that say "space to start" or something like that
}

void GameScreenTitle::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mState = GAMEOVER;
			break;
		}
	}
}

bool GameScreenTitle::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	std::string path = "Assets/Images/Main menu.png";
	if (!mBackgroundTexture->LoadFromFile(path))
	{
		std::cout << "Failed to load main menu background texture at: " << path.c_str();
		return false;
	}
}
