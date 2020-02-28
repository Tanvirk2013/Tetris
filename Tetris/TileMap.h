#pragma once

#include "Constants.h"
#include <iostream>

class TileMap
{
public:
	TileMap();
	~TileMap();

	void LoadMap(std::string path);

	int GetTileAt(unsigned int h, unsigned int w);
	int ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);

protected:
	int** mMap;
};

