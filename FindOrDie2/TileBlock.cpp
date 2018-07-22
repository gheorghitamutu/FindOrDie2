#include "TileBlock.hpp"

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
