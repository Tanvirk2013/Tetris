#pragma once

#include "SDL.h"
#include "Commons.h"
#include <iostream>

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);

	void Free();
	void Render(SDL_Rect srRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
	int rotation;
};

