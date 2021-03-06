#include <utility>

#include "Map.hpp"

map::map() noexcept
{
	tiles_.reserve(1024);
}

map::map(map* other)
{
}

ge::key map::get_key(const sf::Vector2f coords, const std::shared_ptr<camera>& camera) const
{
	const auto view_size = camera->get_current_view()->getSize();

	float x_key = 0;

	if (view_size.x != 0)
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

	if (view_size.y != 0)
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

void map::generate_map(const std::shared_ptr<ge::asset_manager>& asset_manager, const std::shared_ptr<camera>& camera)
{
	set_tiles_in_view(camera);

	for (auto l = 0U; l < levels_count_; l++)
	{
		for (auto i = 0U; i < matrix_tile_size_; i++)
		{
			for (auto j = 0U; j < matrix_tile_size_; j++)
			{
				// TODO: replace dummy random
				if (l == 1)
				{
					bool shouldAddTile = (rand() % 100) < 20;
					if (shouldAddTile == false)
					{
						continue;
					}
				}

				const auto this_tile =
					std::make_shared<tile>(tile(
						asset_manager->get_texture(levels_.find(l)->second),
						tile_type::rock_solid,
						tile_appearance::visible,
						tile_usage::land,
						l));

				this_tile->get_body()->setOrigin(tile_origin_);

				// flat surface formula
				const float tile_position_x = j * half_tile_;
				const float tile_position_y = j * quarter_tile_ + half_tile_ * (i - l);
				this_tile->get_body()->setPosition({ tile_position_x,  tile_position_y });

				const ge::key tile_chunk_position = get_key({ tile_position_x, tile_position_y }, camera);

				auto block_iter = tile_blocks_.find(tile_chunk_position);

				if (block_iter == tile_blocks_.end())
				{
					block_iter = tile_blocks_.insert({ tile_chunk_position, std::make_shared<tile_block>() }).first;
				}

				block_iter->second->emplace_back(this_tile);
			}
		}
	}
}

void map::draw(const std::shared_ptr<sf::RenderWindow>& render_window)
{
	// draw the sorted tiles
	for (auto l = 0U; l < levels_count_; l++)
	{
		for (const auto& tile : tiles_)
		{
			if (tile->get_tile_level() == l)
			{
				render_window->draw(*tile->get_body());
			}
		}
	}
}

void map::update(const std::shared_ptr<camera>& camera, const sf::Vector2f player_position)
{
	tiles_.clear();

	const auto view_center = camera->get_current_view()->getCenter();

	const auto chunk_position = get_key(view_center, camera);

	const auto chunk_identifiers = get_neighbors(chunk_position, neighbors_count_);

	// you get all tiles from all blocks in the view center into one vector of tiles	

	for (const auto& chunk_id : chunk_identifiers)
	{
		const auto tile_block = tile_blocks_.find(chunk_id);

		if (tile_block != tile_blocks_.end())
		{
			const auto block_tiles = tile_block->second->get_tiles();
			tiles_.insert(tiles_.end(), block_tiles->get()->begin(), block_tiles->get()->end());
		}
	}

	for (auto& tile : tiles_)
	{
		if (tile->get_tile_level() == 0)
		{
			continue;
		}

		const sf::Vector2f lower_middle = { player_position.x, player_position.y + 7 };

		if (tile->get_body()->getGlobalBounds().contains(lower_middle))
		{
			tile->get_body()->setColor(transparent_);
		}
		else
		{
			tile->get_body()->setColor(full_color_);
		}
	}

	// then you sort the tiles in order to draw them isometric and not overlap them
	const auto sort_tiles_for_isometric_drawing = [&](std::vector<std::shared_ptr<tile>>& tiles)
	{
		std::sort(tiles.begin(), tiles.end(), [&](const std::shared_ptr<tile> a, const std::shared_ptr<tile> b)
			{
				const auto a_pos = a->get_body()->getPosition();
				const auto b_pos = b->get_body()->getPosition();

				return a_pos.y == b_pos.y ? a_pos.x > b_pos.x : a_pos.y < b_pos.y;
			});
	};

	sort_tiles_for_isometric_drawing(tiles_);
}

void map::set_tiles_in_view(const std::shared_ptr<camera>& camera)
{
	const auto view_size = camera->get_current_view()->getSize();

	// tiles contained by a block relative to view size and tile size
	block_max_tiles_ =
	{
		(view_size.x == 0) ? 0 : static_cast<int>(view_size.x / tile_size_ / tile_factor_),
		(view_size.x == 0) ? 0 : static_cast<int>(view_size.y / tile_size_ / tile_factor_)
	};

	// block size relative to view size (1/4 view size)
	block_size_ =
	{
		(view_size.x == 0) ? 0 : static_cast<int>(view_size.x / tile_factor_),
		(view_size.y == 0) ? 0 : static_cast<int>(view_size.y / tile_factor_)
	};

	std::wcout << "Max tiles on block #[" << block_max_tiles_.x << ", " << block_max_tiles_.y << "]" << std::endl;
	std::wcout << "Max block size #[" << block_size_.x << ", " << block_size_.y << "]" << std::endl;
}
