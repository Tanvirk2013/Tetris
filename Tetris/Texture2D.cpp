#include "Texture2D.h"
#include <SDL_image.h>
#include "Constants.h"


Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}


Texture2D::~Texture2D()
{
	Free();

	mRenderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != nullptr)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		if (mTexture == nullptr)
		{
			std::cout << "Unable to create texture from: " << path.c_str() << std::endl << "Error: " << SDL_GetError() << std::endl;
		}

		mWidth = pSurface->w;
		mHeight = pSurface->h;

		SDL_FreeSurface(pSurface);
	}
	else
	{
		std::cout << "Unable to create texture from: " << path.c_str() << std::endl << "Error: " << SDL_GetError() << std::endl;
	}
	return mTexture != nullptr;
}

void Texture2D::Free()
{
	if (mTexture != nullptr)
	{
		mWidth = 0;
		mHeight = 0;
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, nullptr, flip);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	SDL_RenderCopyEx(mRenderer, mTexture, nullptr, &renderLocation, angle, nullptr, flip);
}