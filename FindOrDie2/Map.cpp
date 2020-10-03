#include <utility>

#include "Map.hpp"

map::map(const std::shared_ptr<ge::game_context>& data) noexcept :
	data_(data)
{
	tiles_.reserve(1024);
}

map::map(map* other)
{
}

ge::key map::get_key(const sf::Vector2f coords) const
{
	const auto view_size = data_->camera_->get_current_view()->getSize();

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

void map::generate_map()
{
	set_tiles_in_view();

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
					data_->asset_manager_));

			this_tile->get_body()->setOrigin({
					static_cast<float>(tile_size_) / 2.f,
					static_cast<float>(tile_size_) / 2.f });

			// flat surface formula
			const float tile_position_x = j * static_cast<float>(tile_size_) / 2;
			const float tile_position_y = i * static_cast<float>(tile_size_) / 2 + j * static_cast<float>(tile_size_) / 4;
			this_tile->get_body()->setPosition({ tile_position_x,  tile_position_y });

			const ge::key tile_chunk_position = get_key({ tile_position_x, tile_position_y });

			if (tile_blocks_.find(tile_chunk_position) == tile_blocks_.end())
			{
				tile_blocks_.insert({ tile_chunk_position, std::make_shared<tile_block>() });
			}

			tile_blocks_[tile_chunk_position]->emplace_back(this_tile);
		}
	}

	for (const auto& tile : tile_blocks_)
	{
		std::wcout << L"TileBlock [" << tile.first.x << ", " << tile.first.y << "] contains #" <<
			tile.second->get_tiles()->get()->size() << " tiles!" << std::endl;
	}

	std::cout << std::endl;

	std::vector<ge::key> keys;
	for (const auto& tile : tile_blocks_)
	{
		keys.emplace_back(tile.first);
	}

	for (const auto& key : keys)
	{
		const auto block_tiles = tile_blocks_[key]->get_tiles();

		std::wcout << L"TileBlock [" << key.x << ", " << key.y << "] contains #" <<
			block_tiles->get()->size() << " tiles!" << std::endl;

		std::vector<std::shared_ptr<tile>> tiles;
		tiles.insert(tiles.end(), block_tiles->get()->begin(), block_tiles->get()->end());
		for (const auto& tile : tiles)
		{
			const auto p = tile->get_body()->getPosition();
			std::wcout << L"X: " << p.x << L" Y: " << p.y << std::endl;
		}
	}
}

void map::draw()
{
	// draw the sorted tiles
	for (const auto& tile : tiles_)
	{
		data_->render_window_->draw(*tile->get_body());
	}
}

void map::update()
{
	tiles_.clear();

	const auto view_center = data_->camera_->get_current_view()->getCenter();

	const auto chunk_position = get_key(view_center);

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

	// then you sort the tiles in order to draw them isometric and not overlap them
	const auto my_sorting = [&](std::vector<std::shared_ptr<tile>>& tiles)
	{
		std::sort(tiles.begin(), tiles.end(), [&](const std::shared_ptr<tile> a, const std::shared_ptr<tile> b)
			{
				const auto a_pos = a->get_body()->getPosition();
				const auto b_pos = b->get_body()->getPosition();
				const auto camera_center = data_->camera_->get_current_view()->getCenter();

				// return (get_clockwise_angle(camera_center, a_pos) > get_clockwise_angle(camera_center, b_pos));
				return a_pos.y == b_pos.y ? a_pos.x > b_pos.x : a_pos.y < b_pos.y;
			});
	};

	// std::wcout << "Drawing #" << tiles_.size() << " tiles!" << std::endl;

	std::vector<std::shared_ptr<tile>> tiles_4;
	std::vector<std::shared_ptr<tile>> tiles_3;
	std::vector<std::shared_ptr<tile>> tiles_2;
	std::vector<std::shared_ptr<tile>> tiles_1;

	const auto camera_center = data_->camera_->get_current_view()->getCenter();
	for (const auto& tile : tiles_) 
	{
		const sf::Vector2f relative_point = tile->get_body()->getPosition() - camera_center;
		switch (get_quadrant(relative_point))
		{
			case 1: tiles_1.emplace_back(tile); break;
			case 2: tiles_2.emplace_back(tile); break;
			case 3: tiles_3.emplace_back(tile); break;
			case 4: tiles_4.emplace_back(tile); break;
		}
	}

	// my_sorting(tiles_1);
	// my_sorting(tiles_2);
	// my_sorting(tiles_3);
	// my_sorting(tiles_4);
	// 
	// tiles_.clear();
	// 
	// const auto my_insert = [&](std::vector<std::shared_ptr<tile>>& tiles)
	// {
	// 	tiles_.insert(tiles_.end(), tiles.begin(), tiles.end());
	// };
	// 
	// my_insert(tiles_4);
	// my_insert(tiles_3);
	// my_insert(tiles_2);
	// my_insert(tiles_1);

	my_sorting(tiles_);
}

void map::set_tiles_in_view()
{
	const auto view_size = data_->camera_->get_current_view()->getSize();

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

int map::get_quadrant(const sf::Vector2f& p)
{
	int result = 4; //origin

	if (p.x > 0 && p.y > 0)
		return 1;
	else if (p.x < 0 && p.y > 0)
		return 2;
	else if (p.x < 0 && p.y < 0)
		return 3;
	//else 4th quadrant
	return result;
}

double map::get_clockwise_angle(const sf::Vector2f& center, const sf::Vector2f& p)
{
	const sf::Vector2f relative_point = p - center;

	double angle = 0.0;
	int quadrant = get_quadrant(relative_point);

	/*calculate angle and return it*/
	angle = -atan2(relative_point.x, -relative_point.y);
	return angle;
}