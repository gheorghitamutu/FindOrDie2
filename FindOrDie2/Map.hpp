#pragma once

#include <vector>
#include <unordered_map>
#include <future>

#include "SFML/Graphics.hpp"

#include "TileBlock.hpp"
#include "GameContext.hpp"

namespace ge
{
	struct key
	{
		int x;
		int y;

		bool operator==(const key &other) const
		{
			return (x == other.x && y == other.y);
		}
	};
}

namespace std 
{
  template <>
  struct hash<ge::key>
  {
    std::size_t operator()(const ge::key& k) const
    {
      using std::size_t;
      using std::hash;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(k.x)
               ^ (hash<int>()(k.y) << 1)) >> 1);
    }
  };
}

class map
{
public:
	explicit map(const std::shared_ptr<ge::game_context>& data) noexcept;

	map(const map& other) = default;
	map(map&& other) noexcept = default;
	explicit map(map* other);
	map& operator=(const map& other) = default;
	map& operator=(map&& other) noexcept = default;

	~map() = default;

	void generate_map();
	void draw();
	void update();
	void set_tiles_in_view();

	const unsigned int tile_size_ = 64;

	const float half_tile_ = static_cast<float>(tile_size_) / 2;
	const float quarter_tile_ = static_cast<float>(tile_size_) / 4;

	const sf::Vector2f tile_origin_{ half_tile_, half_tile_ };

	std::vector<std::shared_ptr<tile>> tiles_;

private:
	ge::key get_key(sf::Vector2f coords) const;
	std::vector<ge::key> get_neighbors(ge::key key, unsigned int levels) const;

	const unsigned int matrix_tile_size_ = 100;
	const unsigned int levels_count_ = 2;
	const unsigned int tile_factor_ = 6U;
	const unsigned int neighbors_count_ = 3U;

	sf::FloatRect view_rect_bounds_;
	std::unordered_map <ge::key, std::shared_ptr<tile_block>> tile_blocks_;
	sf::Vector2<int> block_max_tiles_ = { 0,0 };
	sf::Vector2<int> block_size_ = { 0, 0 };

	std::shared_ptr<ge::game_context> data_;

	const std::map<const unsigned int, const std::string> levels_ = {
		{ 0, "Full_Block_Green" },
		{ 1, "Full_Block_Brown" }
	};
};
