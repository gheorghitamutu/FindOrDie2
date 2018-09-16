#pragma once

#include <vector>
#include <unordered_map>
#include <mutex>

#include "SFML/Graphics.hpp"

#include "AssetManager.hpp"
#include "TileBlock.hpp"

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

class Map
{
public:
	explicit Map(std::shared_ptr<ge::asset_manager> assets) noexcept;

	Map(const Map& other) = default;
	Map(Map&& other) noexcept = default;
	explicit Map(Map* other);
	Map& operator=(const Map& other) = default;
	Map& operator=(Map&& other) noexcept = default;

	~Map() = default;

	void generate_map();
	void draw(sf::RenderWindow* p_window);
	void set_view(const std::shared_ptr<sf::View>& p_view);

	static const unsigned int tile_size = 64;

private:
	ge::key get_key(sf::Vector2f coords) const;
	std::vector<ge::key> get_neighbors(ge::key key, unsigned int levels) const;

	std::shared_ptr<sf::View> p_current_view_ ;
	unsigned long long matrix_tile_size_ = 100;
	sf::FloatRect view_rect_bounds_;
	sf::Vector2f view_size_ = { 0.f, 0.f };
	std::unordered_map < ge::key, std::shared_ptr<tile_block>> tile_blocks_;
	sf::Vector2<int> block_max_tiles_ = { 0,0 };
	sf::Vector2<int> block_size_ = { 0,0 };

	//std::mutex mtx_;

	std::shared_ptr<ge::asset_manager> assets_;
};

