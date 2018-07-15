#include "stdafx.h"
#include "TileBlock.h"


TileBlock::TileBlock()
{
}


TileBlock::~TileBlock()
{
}

std::vector<Tile*>* TileBlock::GetTiles()
{
	return &m_Tiles;
}
