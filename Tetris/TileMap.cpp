#include "TileMap.h"
#include <fstream>

TileMap::TileMap()
{
	mMap = new int*[MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}
}

TileMap::~TileMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}
	delete[] mMap;
}

void TileMap::LoadMap(std::string path)
{
	std::ifstream inFile;
	inFile.open(path);

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int a = 0; a < MAP_WIDTH; a++)
		{
			inFile >> mMap[i][a];
			inFile.ignore(); //Ignore the comma
		}
	}
}

int TileMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}
	return 0;
}

int TileMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue)
{
	if (GetTileAt(column, row) != 0)
	{
		mMap[column][row] = newValue;
	}
	else
		return 0;
}
