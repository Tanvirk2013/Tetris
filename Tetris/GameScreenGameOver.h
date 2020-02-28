#pragma once
#include "GameScreen.h"
class GameScreenGameOver :
	public GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	bool SetUpLevel();
};

