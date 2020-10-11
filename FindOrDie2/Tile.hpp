#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "AssetManager.hpp"

enum class tile_type
{
	rock_solid,
	liquid,
	gas
};

enum class tile_appearance
{
	visible,
	invisible,
	transparent
};

enum class tile_usage
{
	land,
	wall
};

class tile
{
public:
	tile(const std::shared_ptr<sf::Texture>& texture, tile_type type, tile_appearance appearance,
		tile_usage usage, const unsigned int tile_level);
	
	tile(const tile& other) = default;
	tile(tile&& other) noexcept = default;
	explicit tile(tile* other);
	tile& operator=(const tile& other) = default;
	tile& operator=(tile&& other) noexcept = default;
	
	~tile() = default;

	std::shared_ptr<sf::Sprite> get_body() const;
	bool is_visible() const;

	void set_tile_level(const unsigned int tile_level);
	const unsigned int get_tile_level() const;

	const tile_appearance get_tile_appearance() const;
private:
	std::shared_ptr<sf::Sprite> body_;
	std::vector<float> collision_points_;

	tile_type type_ = tile_type::rock_solid;
	tile_appearance appearance_ = tile_appearance::visible;
	tile_usage usage_ = tile_usage::land;

	unsigned int tile_level_ = 0;
};

