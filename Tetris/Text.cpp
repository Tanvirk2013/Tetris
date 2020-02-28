#include"text.h"
#include<iostream>
using namespace std;
Text::Text(SDL_Renderer* renderer, const std::string &fontPath, const int &fontSize, const std::string &messageText, const SDL_Color &color)
{
	textTexture = loadFont(renderer, fontPath, fontSize, messageText, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

}
void Text::display(int x, int y, SDL_Renderer* renderer) const
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}
SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string &fontPath, const int &fontSize, const std::string &messageText, const SDL_Color &color)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font)
	{
		cout << "failed to load font" << endl;
	}
	auto textSurface = TTF_RenderText_Solid(font, messageText.c_str(), color);
	if (!textSurface)
	{
		cout << "failed to create text surface" << endl;
	}
	auto textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture)
	{
		cout << "failed to create text texture" << endl;
	}
	SDL_FreeSurface(textSurface);
	return textTexture;
}
void Text::Update(SDL_Renderer* renderer, const std::string &fontPath, const int &fontSize, const std::string &messageText, const SDL_Color &color)
{
	textTexture = loadFont(renderer, fontPath, fontSize, messageText, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}