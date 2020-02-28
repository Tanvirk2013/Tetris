#pragma once

#include "Character.h"

class CharacterTetrominoOutline : public Character
{
public:
	CharacterTetrominoOutline(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map);
	~CharacterTetrominoOutline();

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
	bool lockBlock;
	bool mGameOver;
	bool callInstantDrop;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
};

