#include "TileBlock.h"


TileBlock::TileBlock() noexcept
{
}


TileBlock::~TileBlock()
{
}

std::vector<Tile*>* TileBlock::GetTiles()
{
	return &m_Tiles;
}
