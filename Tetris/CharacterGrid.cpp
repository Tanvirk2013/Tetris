#include "CharacterGrid.h"

//Renderer for placed blocks

CharacterGrid::CharacterGrid(SDL_Renderer * renderer, std::string imagePath, Vector2D startPosition, TileMap * map) : Character(renderer, imagePath, startPosition, map)
{
	mRenderer = renderer;
	mSpriteSheetX = 32;
	mSpriteSheetY = 32;
	Points = 0;
	Lines = 0;
	Cleared = 0;
}

CharacterGrid::~CharacterGrid()
{
	Character::~Character();
}

void CharacterGrid::Render()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int a = 0; a < MAP_WIDTH; a++)
		{
			switch (mCurrentTileMap->GetTileAt(i, a))
			{
			case 0:
				mShapeColour = CLEAR;
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
		}
	}
}

void CharacterGrid::Update(float deltaTime, SDL_Event e)
{
	CheckLines();
}

void CharacterGrid::CheckLines()
{
	int count = 0;
	for (int i = 0; i < MAP_HEIGHT; i++) 
	{
		for (int a = 0; a < MAP_WIDTH; a++)
		{
			if (mCurrentTileMap->GetTileAt(i, a) >= 2)
				count++;
			else
				count = 0;

			if (count == 10)
			{
				Cleared ++;
				for (int b = 5; b < 15; b++)
				{
					// clear full line
					mCurrentTileMap->ChangeTileAt(b, i, 1);
					// blocks fall
					for (int j = i; j > 1; j--)
						mCurrentTileMap->ChangeTileAt(b, j, mCurrentTileMap->GetTileAt(j - 1, b));
					
				}
				for (int b = 5; b < 15; b++)
				{
					mCurrentTileMap->ChangeTileAt(b, 1, 1);
				}
			}	
		}
	}

	Lines += Cleared;
	if (Cleared == 1)
	{
		Points += 10;
	}
	else if (Cleared == 2)
	{
		Points += 30;
	}
	else if (Cleared == 3)
	{
		Points += 60;
	}
	else if (Cleared == 4)
	{
		Points += 100;
	}
	Cleared = 0;
}
