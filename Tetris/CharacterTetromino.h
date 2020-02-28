#pragma once

#include "Character.h"

class CharacterTetromino : public Character
{
public:
	CharacterTetromino(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map);
	~CharacterTetromino();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetColour(COLOURS colour);
	void SetAlive(bool status);

	bool GetGameOver() { return mGameOver; }
	bool GetAlive() { return mAlive; }
	
	COLOURS GetColour() { return mShapeColour; }
	
protected:
	Mix_Chunk* mSoundGravity;

	SDL_Rect blockDest[4];

	int mChosenShape[4];
	int mBlockX[4];
	int mBlockY[4];
	int mTimer;

	bool mAlive;
	bool mGameOver;
	bool lockBlock;
	bool callInstantDrop;

	bool CheckLeft(int yVal[4], int xVal[4]);
	bool CheckRight(int yVal[4], int xVal[4]);

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	void RotateBlockLeft(float deltaTime);
	void RotateBlockRight(float deltaTime);
	void InstantDrop();
	void PlaceBlock();
	void AddGravity();
	void InitialiseSounds();
	void PositionBlocks();
};

