#pragma once
#include "Tile.hpp"

class tile_block
{
public:
	tile_block() noexcept = default;

	tile_block(const tile_block& other) = default;
	tile_block(tile_block&& other) noexcept = default;
	tile_block& operator=(const tile_block& other) = default;
	tile_block& operator=(tile_block&& other) noexcept = default;

	~tile_block() = default;

	const std::shared_ptr<std::vector<std::shared_ptr<tile>>>* get_tiles() const;
	void emplace_back(std::shared_ptr<tile> tile);
	
private:
	std::shared_ptr<std::vector<std::shared_ptr<tile>>> m_tiles_ = 
		std::make_shared<std::vector<std::shared_ptr<tile>>>(std::vector<std::shared_ptr<tile>>());
};

