#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "GameScreenManager.h"
#include "Commons.h"

using std::cout;

//Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
GameScreenManager* gScreenManager;
Uint32 gOldTime;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		gScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);

		gOldTime = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "SDL_Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}
		gWindow = SDL_CreateWindow("TETRIS",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == nullptr)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != nullptr)
		{
			//Initialise PNG Loading
			int imageFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		if (TTF_Init() < 0)
		{
			std::cout << "SDL_TTF could not initialise. Error: " << TTF_GetError() << std::endl;
			return false;
		}
	}
	return true;
}

void CloseSDL()
{	
	delete gScreenManager;
	gScreenManager = nullptr;
	
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();
	//Event Handler
	SDL_Event e;
	SDL_PollEvent(&e);

	if (e.type == SDL_QUIT)
		return true;

	gScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}


