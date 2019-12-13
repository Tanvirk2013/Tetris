#include "GameScreenLevelOne.h"
#include <iostream>
#include "Texture2D.h"
#include <stdlib.h> 
#include <ctime>

GameScreenLevelOne::GameScreenLevelOne(SDL_Renderer * renderer) : GameScreen(renderer)
{
	srand(time(0));
	SetUpLevel();
}

GameScreenLevelOne::~GameScreenLevelOne()
{
	// inherits background texture deletion from GameScreen

	delete mTetrominoCharacter;
	mTetrominoCharacter = nullptr;
	mTetrominoes.clear();
	delete mPlayField;
	mPlayField = nullptr;
	delete mText;
	mText = nullptr;
	delete mLines;
	mLines = nullptr;
}

void GameScreenLevelOne::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, 0.0);
	mPlayField->Render();

	mText->display(495, 490, mRenderer);
	mLines->display(495, 530, mRenderer);

	for (unsigned int i = 0; i < mTetrominoes.size(); i++)
		mTetrominoes[i]->Render();
}

void GameScreenLevelOne::Update(float deltaTime, SDL_Event e)
{
	mPlayField->Update(deltaTime, e);
	UpdateTetromino(deltaTime, e);

	if (mPlayField->Points > PointCount)
	{
		mText->Update(mRenderer, "Assets/Images/ARCADE_N.ttf", 12, "Score:" + std::to_string(mPlayField->Points), { 255, 255, 255, 255 });
		PointCount = mPlayField->Points;
		mLines->Update(mRenderer, "Assets/Images/ARCADE_N.ttf", 12, "lines:" + std::to_string(mPlayField->Lines), { 255, 255, 255, 255 });
		LineCount = mPlayField->Lines;
	}
}

bool GameScreenLevelOne::SetUpLevel()
{
	mAudioMgr = new AudioManager;
	mAudioMgr->PlayMusic("Assets/Audio/Mario.mp3");
	SetTileMap();
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Assets/Images/Background.png"))
	{
		std::cout << "Failed to load background texture at";
		return false;
	}
	mPlayField = new CharacterGrid(mRenderer, "Assets/Images/Tetris tiles.png", Vector2D(32 * 5, 32), mTileMap);
	mPlayField->Points = 0;
	PointCount = mPlayField->Points;
	mPlayField->Lines= 0;
	LineCount = mPlayField->Lines;
	mText = new Text(mRenderer, "Assets/Images/ARCADE_N.ttf", 12, "Score: " + std::to_string(mPlayField->Points), { 255, 255, 255, 255 });
	mLines = new Text(mRenderer, "Assets/Images/ARCADE_N.ttf", 12, "lines: " + std::to_string(mPlayField->Lines), { 255, 255, 255, 255 });

	// fill tetromino queue
	for (unsigned int i = 0; i < 4; i++)
		CreateTetromino();
	ShiftTetrominoes();
}

void GameScreenLevelOne::SetTileMap()
{
	if (mTileMap != nullptr)
	{
		delete mTileMap;
	}
	mTileMap = new TileMap;
	mTileMap->LoadMap("Assets/TileMaps/Playfield.txt");
}

void GameScreenLevelOne::CreateTetromino()
{
	mTetrominoCharacter = new CharacterTetromino(mRenderer, "Assets/Images/Tetris tiles.png", Vector2D(32 * 9, 32), mTileMap);
	mTetrominoes.push_back(mTetrominoCharacter);
	Randomiser();
}

void GameScreenLevelOne::UpdateTetromino(float deltaTime, SDL_Event e)
{
	// first tetromino = active, others = queue
	// mTetrominoes should never be empty
	mTetrominoes[0]->Update(deltaTime, e);

	//Check for gameover and collision
	if (mTetrominoes[0]->GetGameOver())
		mState = GAMEOVER;

	else if (!mTetrominoes[0]->GetAlive())
	{
		mTetrominoes.erase(mTetrominoes.begin());
		CreateTetromino();

		// shift positions of tetrominoes
		mTetrominoes[0]->SetPosition(Vector2D(32 * 9, 32));
		ShiftTetrominoes();
	}
}

void GameScreenLevelOne::Randomiser()
{
	if (counter == 7)
	{
		for (int j = 0; j < 7; j++)
		{
			Pieces[j] = 1;
		}
		counter = 0;
	}
	i = rand() % 7 + 0;
	available = Pieces[i];
	if (Pieces[i] == 1)
	{
		if (i == 0)
		{
			mColour = PURPLE;
		}
		else if (i == 1)
		{
			mColour = LBLUE;
		}
		else if (i == 2)
		{
			mColour = ORANGE;
		}
		else if (i == 3)
		{
			mColour = RED;
		}
		else if (i == 4)
		{
			mColour = YELLOW;
		}
		else if (i == 5)
		{
			mColour = DBLUE;
		}
		else if (i == 6)
		{
			mColour = GREEN;
		}
		Pieces[i] = 0;
		counter++;
	}
	else if (Pieces[i] == 0)
	{
		Randomiser();
	}
	
	mTetrominoes[mTetrominoes.size() - 1]->SetColour(mColour);
}

void GameScreenLevelOne::ShiftTetrominoes()
{
	mTetrominoes[1]->SetPosition(Vector2D(540, 42));
	mTetrominoes[2]->SetPosition(Vector2D(540, 170));
	mTetrominoes[3]->SetPosition(Vector2D(540, 298));
}