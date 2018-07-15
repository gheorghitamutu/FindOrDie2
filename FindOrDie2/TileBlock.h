#pragma once
#include "Tile.h"


class TileBlock
{
public:
	TileBlock();
	~TileBlock();
	std::vector<Tile*>* GetTiles();

private:
	std::vector<Tile*> m_Tiles;
};

