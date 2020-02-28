#include "CharacterTetromino.h"

int mShapes[7][4] =
{
	//Tetromino shapes 
	{0,2,4,6}, // I 
	{0,2,3,5}, // Z
	{1,3,2,4}, // S
	{1,3,2,5}, // T
	{0,1,3,5}, // L
	{1,3,5,4}, // J
	{0,1,2,3}, // O
};

CharacterTetromino::CharacterTetromino(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mAlive = true;
	lockBlock = false;
	mRenderer = renderer;
	mSpriteSheetX = 32;
	mSpriteSheetY = 32;
	mTimer = GRAVITY_TIMER;
	mGameOver = false;
}

CharacterTetromino::~CharacterTetromino()
{
	Character::~Character();
}

void CharacterTetromino::Render()
{
	SDL_Rect portionOfSpriteSheet = { mShapeColour, 0, mSpriteSheetX, mSpriteSheetY };
	for (int i = 0; i < 4; i++)
	{
		blockDest[i] = { mBlockX[i] + (int)(mPosition.x), mBlockY[i] + (int)(mPosition.y), mSpriteSheetX, mSpriteSheetY };
		mTexture->Render(portionOfSpriteSheet, blockDest[i], mFacingDirection, 0.0);
	}
}

void CharacterTetromino::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			MoveLeft(deltaTime);
			break;
		case SDLK_RIGHT:
			MoveRight(deltaTime);
			break;
		case SDLK_DOWN:
			AddGravity();
			break;
		case SDLK_UP:
			callInstantDrop = true;
			mAudioMgr->PlaySound(mSoundGravity);
			break;
		case SDLK_SPACE:
			//std::cout << "X: " << mPosition.x << " Y: " << mPosition.y << std::endl;
			break;
		case SDLK_z:
			//mCalledRotation = true;
			RotateBlockLeft(deltaTime);
			break;
		case SDLK_x:
			RotateBlockRight(deltaTime);
			break;
		default:
			break;
		}
	}

	if (callInstantDrop)
		InstantDrop();

	mTimer -= deltaTime;
	if (mTimer <= 0.0f)
	{
		mTimer = GRAVITY_TIMER;
		AddGravity();
	}

	for (int i = 0; i < 4; i++)
	{
		//Check if one block below is a block or the playfield
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) >= 2 ||
			(mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 0))
		{
			lockBlock = true;
		}

		//Check if block below and above are either occupied or not available
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y - mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 0 && lockBlock)
		{
			//lockBlock is called when a block is below so it can be reused
			mGameOver = true;
		}
	}

	if (lockBlock)
		PlaceBlock();
}

void CharacterTetromino::SetColour(COLOURS colour)
{
	mShapeColour = colour;
	int a;
	switch (mShapeColour)
	{
	case PURPLE:
		//T block
		a = 3;
		break;
	case RED:
		//Z block
		a = 2;
		break;
	case ORANGE:
		//L block
		a = 4;
		break;
	case YELLOW:
		//O block
		a = 6;
		break;
	case DBLUE:
		//R block
		a = 5;
		break;
	case LBLUE:
		//I block
		a = 0;
		break;
	case GREEN:
		//S block
		a = 1;
		break;
	}

	for (int i = 0; i < 4; i++)
		mChosenShape[i] = mShapes[a][i];

	PositionBlocks();
}

void CharacterTetromino::SetAlive(bool status)
{
	mAlive = status;
}

void CharacterTetromino::MoveLeft(float deltaTime)
{
	int tempX[4];
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		//Check if blocks on the left are equal to 1
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y) / mSpriteSheetY, ((int)(mBlockX[i] + mPosition.x) - mSpriteSheetX) / mSpriteSheetX) == 1)
			count++;
		else
			break;
	}
	if (count == 4)
		mPosition.x -= TILE_WIDTH;
}

void CharacterTetromino::MoveRight(float deltaTime)
{
	int tempX[4];
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x + mSpriteSheetX) / mSpriteSheetX) == 1)
			count++;
		else
			break;
	}
	if (count == 4)
		mPosition.x += TILE_WIDTH;
}

bool CharacterTetromino::CheckLeft(int yVal[4], int xVal[4])
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (mCurrentTileMap->GetTileAt((yVal[i] + mPosition.y) / mSpriteSheetY, ((xVal[i] + mPosition.x) - mSpriteSheetX) / mSpriteSheetX) == 1)
			count++;
		else
		{
			return false;
		}
	}
	if (count == 4)
	{
		return true;
	}
}

bool CharacterTetromino::CheckRight(int yVal[4], int xVal[4])
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		//Check if blocks on the left are equal to 1
		if (mCurrentTileMap->GetTileAt((yVal[i] + mPosition.y) / mSpriteSheetY, (xVal[i] + mPosition.x + mSpriteSheetX) / mSpriteSheetX) == 1)
			count++;
		else
		{
			return false;
		}
	}
	if (count == 4)
	{
		return true;
	}
}

void CharacterTetromino::RotateBlockRight(float deltaTime)
{
	if (!(mShapeColour == YELLOW))
	{
		int tempX[4];
		int tempY[4];
		bool check = true;
		Vector2D centre = Vector2D(mBlockX[1], mBlockY[1]);

		for (int i = 0; i < 4; i++)
		{
			tempX[i] = mBlockY[i] - centre.y;
			tempY[i] = mBlockX[i] - centre.x;
		}
		if (CheckRight(tempY, tempX) == true) check = false;
		if (!check)
		{
			for (int i = 0; i < 4; i++)
			{
				mBlockX[i] = centre.x - tempX[i];
				mBlockY[i] = centre.y + tempY[i];
			}
		}
	}
}

void CharacterTetromino::RotateBlockLeft(float deltaTime)
{
	if (!(mShapeColour == YELLOW))
	{
		int tempX[4];
		int tempY[4];
		bool check = true;
		Vector2D centre = Vector2D(mBlockX[1], mBlockY[1]);

		for (int i = 0; i < 4; i++)
		{
			tempX[i] = mBlockY[i] - centre.y;
			tempY[i] = mBlockX[i] - centre.x;
		}
		if (CheckLeft(tempY, tempX) == true) check = false;
		if (!check)
		{
			for (int i = 0; i < 4; i++)
			{
				mBlockX[i] = centre.x + tempX[i];
				mBlockY[i] = centre.y - tempY[i];
			}
		}
	}
}

void CharacterTetromino::InstantDrop()
{
	int count = 0;
	int drop = 0;
	bool falling = false;
	for (int a = 0; a < MAP_WIDTH; a++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + (mSpriteSheetY + (mSpriteSheetY * a))) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 1)
				count++;

			else
			{
				falling = true;
				break;
			}

		}
		if (count == 4)
		{
			drop++;
			count = 0;
		}
		if (falling) break;
	}

	callInstantDrop = false;
	mPosition.y += drop * TILE_WIDTH;
	mAlive = false;

}

void CharacterTetromino::PlaceBlock()
{
	for (int i = 0; i < 4; i++)
		mCurrentTileMap->ChangeTileAt((mBlockX[i] + mPosition.x) / mSpriteSheetX, (mBlockY[i] + mPosition.y) / mSpriteSheetY, mShapeColour / 32);

	mAlive = false;
}

void CharacterTetromino::AddGravity()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 1)
			count++;

		else
		{
			callInstantDrop = false;
			break;
		}

	}
	if (count == 4)
	{
		mAudioMgr->PlaySound(mSoundGravity);
		mPosition.y += TILE_HEIGHT;
	}
}

void CharacterTetromino::InitialiseSounds()
{
	mSoundGravity = Mix_LoadWAV("Assets/Audio/PlayerDeath.wav");
}

void CharacterTetromino::PositionBlocks()
{
	// mChosenShape is what will be rendered.
// We only need 1 source rect
// blockDest is an array used for our destination rectangle
//Switch case doesn't need the numbers that are missing
	for (int i = 0; i < 4; i++)
	{
		switch (mChosenShape[i])
		{

		case 1:
			mBlockX[i] = mSpriteSheetX;
			mBlockY[i] = 0;
			break;
		case 2:
			mBlockX[i] = 0;
			mBlockY[i] = mSpriteSheetY;
			break;
		case 3:
			mBlockX[i] = mSpriteSheetX;
			mBlockY[i] = mSpriteSheetY;
			break;
		case 4:
			mBlockX[i] = 0;
			mBlockY[i] = mSpriteSheetY * 2;
			break;
		case 5:
			mBlockX[i] = mSpriteSheetX;
			mBlockY[i] = mSpriteSheetY * 2;
			break;
		case 6:
			mBlockX[i] = 0;
			mBlockY[i] = mSpriteSheetY * 3;
			break;
		case 7:
			mBlockX[i] = mSpriteSheetX;
			mBlockY[i] = mSpriteSheetY * 3;
			break;
		}
	}
}
