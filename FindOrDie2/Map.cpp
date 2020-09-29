#include <utility>

#include "Map.hpp"

map::map(std::shared_ptr<ge::asset_manager> assets) noexcept :
	assets_(std::move(assets))
{
}

map::map(map* other)
{
}

ge::key map::get_key(const sf::Vector2f coords) const
{
	float x_key = 0;

	if (view_size_.x != 0)
	{
		x_key = coords.x / block_size_.x;

		if (x_key < 0)
		{
			x_key -= 1;
		}
		else
		{
			x_key += 1;
		}
	}

	float y_key = 0;

	if (view_size_.y != 0)
	{
		y_key = coords.y / block_size_.y;

		if (y_key < 0)
		{
			y_key -= 1;
		}
		else
		{
			y_key += 1;
		}
	}

	return { static_cast<int>(x_key), static_cast<int>(y_key) };
}

std::vector<ge::key> map::get_neighbors(const ge::key key, const unsigned int levels) const
{
	std::vector<ge::key> blocks_coords;

	// compute lowest x and y coords
	int low_x = key.x - levels;
	int low_y = key.y - levels;

	// compute highest x and y coords
	int high_x = key.x + levels;
	int high_y = key.y + levels;

	// if neighbors pass from one Q to another (from Q1 to Q2, from Q3 to Q4, etc)
	// make sure you handle the transition skipping (0,0), (0,1), (1,0), (-1,0), (0,-1)
	// as the key lowest values for Qs are (1,1), (-1,1), (1,-1), (-1,-1)
	// and increase all the neighbors from that side with 1 << (0, 1) -> (1,2) >>

	const int abs_x = abs(key.x) - levels;
	const int abs_y = abs(key.y) - levels;

	if (abs_x <= 1 || abs_y <= 1)
	{
		// transition Q1 or Q4 to Q2 or Q3
		if (key.x > 0 && low_x <= 0)
		{
			low_x--;
		}

		// transition Q2 or Q3 to Q1 or Q4
		if (key.x < 0 && high_x >= 0)
		{
			high_x++;
		}

		// transition Q1 or Q2 to Q3 or Q4
		if (key.y > 0 && low_y <= 0)
		{
			low_y--;
		}

		// transition Q3 or Q4 to Q1 or Q2
		if (key.y < 0 && high_y >= 0)
		{
			high_y++;
		}
	}

	// previously increasing the limits if transitions are happening
	// we can now ignore every pair with 0s (0,1), (1,0), (-1,0), (0,-1)
	// and add all the others
	auto index_x = low_x;
	auto index_y = low_y;
	for (; index_x <= high_x; index_x++)
	{
		for (; index_y <= high_y; index_y++)
		{
			if (index_x != 0 && index_y != 0)
			{
				const ge::key block_key = { index_x, index_y };
				blocks_coords.emplace_back(block_key);
			}
		}

		index_y = low_y;
	}

	return blocks_coords;
}

void map::generate_map()
{
	for (auto i = 0U; i < matrix_tile_size_; i++)
	{
		for (auto j = 0U; j < matrix_tile_size_; j++)
		{
			const auto this_tile =
				std::make_shared<tile>(tile(
					"Full_Block",
					rock_solid,
					visible,
					land,
					assets_));

			this_tile->get_body()->setOrigin({
					static_cast<float>(tile_size_) / 2.f,
					static_cast<float>(tile_size_) / 2.f });

			// flat surface formula
			const float tile_position_x = j * static_cast<float>(tile_size_) / 2;
			const float tile_position_y = i * static_cast<float>(tile_size_) / 4 + j * static_cast<float>(tile_size_) / 4;
			this_tile->get_body()->setPosition({ tile_position_x,  tile_position_y });

			const ge::key tile_chunk_position = get_key({ tile_position_x, tile_position_y });

			if (tile_blocks_.find(tile_chunk_position) == tile_blocks_.end())
			{
				tile_blocks_.insert({ tile_chunk_position, std::make_shared<tile_block>() });
			}

			tile_blocks_[tile_chunk_position]->emplace_back(this_tile);
		}
	}
}

void map::draw(const std::unique_ptr<sf::RenderWindow>& p_window)
{
	const auto view_center = p_current_view_->getCenter();

	const auto chunk_position = get_key(view_center);

	const auto chunk_identifiers = get_neighbors(chunk_position, 2);

	// you get all tiles from all blocks in the view center into one vector of tiles
	std::vector<std::shared_ptr<tile>> tiles;

	for (const auto& chunk_id : chunk_identifiers)
	{
		const auto tile_block = tile_blocks_.find(chunk_id);

		if (tile_block != tile_blocks_.end())
		{
			const auto block_tiles = tile_block->second->get_tiles();
			tiles.insert(tiles.end(), block_tiles->get()->begin(), block_tiles->get()->end());
		}
	}

	// then you sort the tiles in order to draw them isometric and not overlap them
	std::sort(tiles.begin(), tiles.end(), [&](const std::shared_ptr<tile> a, const std::shared_ptr<tile> b)
		{
			const auto a_pos = a->get_body()->getPosition();
			const auto b_pos = b->get_body()->getPosition();

			return a_pos.y == b_pos.y ? a_pos.x > b_pos.x : a_pos.y < b_pos.y;
		});

	// draw the sorted tiles
	for (const auto& tile : tiles)
	{
		p_window->draw(*tile->get_body());
	}
}

void map::set_view(const std::shared_ptr<sf::View>& p_view)
{
	p_current_view_ = p_view;

	view_size_ = p_current_view_->getSize();

	// tiles contained by a block relative to view size and tile size
	block_max_tiles_ =
	{
		(view_size_.x == 0) ? 0 : static_cast<int>(view_size_.x / tile_size_ / 2),
		(view_size_.x == 0) ? 0 : static_cast<int>(view_size_.y / tile_size_ / 2)
	};

	// block size relative to view size (1/4 view size)
	block_size_ =
	{
		(view_size_.x == 0) ? 0 : static_cast<int>(view_size_.x / 2),
		(view_size_.y == 0) ? 0 : static_cast<int>(view_size_.y / 2)
	};
}
