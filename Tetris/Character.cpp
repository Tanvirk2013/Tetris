#include "Character.h"
#include "Constants.h"

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

	SetPosition(startPosition);

	mFacingDirection = SDL_FLIP_NONE;
}

Character::~Character()
{
	mRenderer = nullptr;
	delete mAudioMgr;
	mAudioMgr = nullptr;
	mCurrentTileMap = nullptr;
	delete mCurrentTileMap;
}

void Character::Render()
{

}

void Character::Update(float deltaTime, SDL_Event e)
{

}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void Character::MoveLeft(float deltaTime)
{
}

void Character::MoveRight(float deltaTime)
{
}

void Character::InitialiseSounds()
{

}

