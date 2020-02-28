#pragma once

#include "GameScreen.h"
#include <SDL.h>
#include "Commons.h"
#include "Character.h"
#include "CharacterGrid.h"
#include "CharacterTetromino.h"
#include "AudioManager.h"
#include "TileMap.h"
#include "Text.h"
#include <vector>

class Texture2D;
class Character;
class AudioManager;
class TileMap;

class GameScreenTetris : GameScreen
{
public:
	GameScreenTetris(SDL_Renderer* renderer);
	~GameScreenTetris();
	
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	std::vector<CharacterTetromino*> mTetrominoes; 
	CharacterTetromino* mTetrominoCharacter;
	CharacterGrid* mPlayField;
	AudioManager* mAudioMgr;
	TileMap* mTileMap;
	Text* mText;
	Text* mLines;
	COLOURS mColour;

	bool SetUpLevel();

	int PointCount;
	int LineCount;
	
	int Pieces[7] = { 1,1,1,1,1,1,1 };
	int i = 0;
	int counter = 0;
	int available = 0;

	void Randomiser();
	void SetTileMap();
	void CreateTetromino();
	void UpdateTetromino(float deltaTime, SDL_Event e);
	void ShiftTetrominoes();
};

