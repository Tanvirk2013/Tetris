#pragma once

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "AudioManager.h"
#include "Texture2D.h"
#include <SDL_mixer.h>
#include "TileMap.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);

	Vector2D GetPosition() { return mPosition; }
	
protected:
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;
	AudioManager* mAudioMgr;
	TileMap* mCurrentTileMap;

	Vector2D mPosition;
	COLOURS mShapeColour;
	SDL_RendererFlip mFacingDirection;

	int mSpriteSheetX;
	int mSpriteSheetY;
	int mBlockX[4];
	int mBlockY[4];

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void InitialiseSounds();
};

