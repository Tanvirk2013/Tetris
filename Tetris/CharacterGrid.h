#pragma once

#include "Character.h"

class CharacterGrid : public Character
{
public:
	CharacterGrid(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map);
	~CharacterGrid();
	int Points;
	int Cleared;
	int Lines;
	void Render();
	void Update(float deltaTime, SDL_Event e);

	void CheckLines();
};

