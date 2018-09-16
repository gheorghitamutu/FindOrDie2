#include "TileBlock.hpp"

std::shared_ptr<std::vector<std::shared_ptr<tile>>> tile_block::get_tiles() const
{
	return m_tiles_;
}
