#include "TileBlock.hpp"

const std::shared_ptr<std::vector<std::shared_ptr<tile>>>* tile_block::get_tiles() const
{
	return &m_tiles_;
}

void tile_block::emplace_back(std::shared_ptr<tile> tile)
{
	m_tiles_->emplace_back(tile);
}
