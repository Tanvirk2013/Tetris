#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

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

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map)
{
	mAudioMgr = new AudioManager;
	if (mAudioMgr != nullptr)
		InitialiseSounds();
	mRenderer = renderer;
	mCurrentTileMap = map;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
		std::cout << "Character at path: " << imagePath.c_str() << " could not be loaded." << std::endl;

	mSpriteSheetX = 32;
	mSpriteSheetY = mTexture->GetHeight();

	SetPosition(startPosition);

	for (int i = 0; i < 4; i++)
		mChosenShape[i] = mShapes[6][i]; // replace 3 with random

	positionBlocks();
	mMovingLeft = false;
	mMovingRight = false;
	mCalledRotation = false;
	mMovementSpeed = 32.0f;
	mGravity = 32.0f;
	mTimer = 3.0f;
	mFacingDirection = SDL_FLIP_NONE;
}

Character::~Character()
{
	mRenderer = nullptr;
	delete mAudioMgr;
	mAudioMgr = nullptr;
	delete mSoundGravity;
	mSoundGravity = nullptr;
	mCurrentTileMap = nullptr;
	delete mCurrentTileMap;
}

void Character::Render()
{	
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int a = 0; a < MAP_WIDTH; a++)
		{
			switch (mCurrentTileMap->GetTileAt(i, a))
			{
			case 0:
				mShapeColour = WHITE;
				break;
			case 1:
				mShapeColour = CLEAR;
				break;
			case 2:
				mShapeColour = LBLUE;
				break;
			case 3:
				mShapeColour = DBLUE;
				break;
			case 4:
				mShapeColour = ORANGE;
				break;
			case 5:
				mShapeColour = YELLOW;
				break;
			case 6:
				mShapeColour = GREEN;
				break;
			case 7:
				mShapeColour = RED;
				break;
			case 8:
				mShapeColour = PURPLE;
				break;
			default:
				mShapeColour = CLEAR;
				break;
			}
			SDL_Rect portionOfSpriteSheet = { mShapeColour, 0, mSpriteSheetX, mSpriteSheetY };
			SDL_Rect destRect{ a * mSpriteSheetX, i * mSpriteSheetY, mSpriteSheetX, mSpriteSheetY };
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0.0);

			CurrentTetromino();
		}
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (mMovingLeft)
		MoveLeft(deltaTime);

	if (mMovingRight)
		MoveRight(deltaTime);

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
		case SDLK_SPACE:
			//mPosition.y = 576.0f; // quick drop
			std::cout << "X: " << mPosition.x << " Y: " << mPosition.y << std::endl;
			break;
		case SDLK_z:
			mCalledRotation = true;
			break;
		case SDLK_x:
			break;
		default:
			break;
		}
	}

	mTimer -= deltaTime;
	if (mTimer <= 0.0f)
	{
		mTimer = 3.0f;
		//AddGravity();
	}

	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		default:
			break;
		}
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void Character::SetColour(COLOURS colour)
{
	mShapeColour = colour;
}

void Character::MoveLeft(float deltaTime)
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
		mPosition.x -= mMovementSpeed;
}

void Character::MoveRight(float deltaTime)
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
		mPosition.x += mMovementSpeed;
}

void Character::rotateBlocks(ROTATION direction)
{
	Vector2D centre;
	centre.x = mBlockX[1];
	centre.y = mBlockY[1];
	for (int i = 0; i < 4; i++)
	{
		int tempX = mBlockY[i] - centre.y;
		int tempY = mBlockX[i] - centre.x;
		mBlockX[i] = centre.x - tempX;
		mBlockY[i] = centre.y + tempY;
	}
	mCalledRotation = false;
}

void Character::positionBlocks()
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

void Character::AddGravity()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 1)
			count++;

		else
			break;
	}
	if (count == 4)
	{
		mAudioMgr->PlaySound(mSoundGravity);l
		mPosition.y += mGravity;
	}
		

	for (int i = 0; i < 4; i++)
	{
		if (mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) >= 2 ||
			(mCurrentTileMap->GetTileAt((int)(mBlockY[i] + mPosition.y + mSpriteSheetY) / mSpriteSheetY, (int)(mBlockX[i] + mPosition.x) / mSpriteSheetX) == 0))
			mCurrentTileMap->ChangeTileAt((mBlockX[i] + mPosition.x) / mSpriteSheetX, (mBlockY[i] + mPosition.y) / mSpriteSheetY, mShapeColour / 32);
	}
}

void Character::InitialiseSounds()
{
	mSoundGravity = Mix_LoadWAV("Assets/Audio/PlayerDeath.wav");
}

void Character::CurrentTetromino()
{
	mShapeColour = RED;
	SDL_Rect portionOfSpriteSheet = { mShapeColour, 0, mSpriteSheetX, mSpriteSheetY };
	if (mCalledRotation)
		rotateBlocks(mRotation);

	for (int i = 0; i < 4; i++)
	{
		blockDest[i] = { mBlockX[i] + (int)(mPosition.x), mBlockY[i] + (int)(mPosition.y), mSpriteSheetX, mSpriteSheetY };
		mTexture->Render(portionOfSpriteSheet, blockDest[i], mFacingDirection, 0.0);
	}
}
