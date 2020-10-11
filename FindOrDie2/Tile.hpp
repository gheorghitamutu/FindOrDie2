#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "AssetManager.hpp"

enum tile_type
{
	rock_solid,
	liquid,
	gas
};

enum tile_appearance
{
	visible,
	invisible,
	transparent
};

enum tile_usage
{
	land,
	wall
};

class tile
{
public:
	tile(const std::string& name, tile_type type, tile_appearance appearance, 
		tile_usage usage, const unsigned int tile_level, 
		const std::shared_ptr<ge::asset_manager>& assets);
	
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
private:
	std::shared_ptr<sf::Sprite> body_;
	std::vector<float> collision_points_;

	tile_type type_ = rock_solid;
	tile_appearance appearance_ = visible;
	tile_usage usage_ = land;

	unsigned int tile_level_ = 0;
};

