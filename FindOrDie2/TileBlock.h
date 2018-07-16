#pragma once
#include "Tile.h"


class TileBlock
{
public:
	TileBlock() noexcept;
	~TileBlock();
	std::vector<Tile*>* GetTiles();

private:
	std::vector<Tile*> m_Tiles;
};

