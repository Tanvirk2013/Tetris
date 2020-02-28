#include "GameScreenGameOver.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenGameOver::~GameScreenGameOver()
{
	// inherits background texture deletion from GameScreen
}

void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, 0.0);
	// TODO score display, "press space to return to main menu"
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
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

bool GameScreenGameOver::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Assets/Images/Game over.png"))
	{
		std::cout << "Failed to load game over background texture";
		return false;
	}
}
