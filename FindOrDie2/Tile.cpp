#include "Tile.hpp"

tile::tile(const std::string& name, const tile_type type, const tile_appearance appearance,
           const tile_usage usage, const unsigned int tile_level,
		   const std::shared_ptr<ge::asset_manager>& assets) :
	type_(type),
	appearance_(appearance),
	usage_(usage),
	tile_level_(tile_level)
{
	body_ = std::make_shared<sf::Sprite>(sf::Sprite());

	const auto body_texture = assets->get_texture(name);
	
	if (body_texture != nullptr)
	{
		body_->setTexture(*body_texture);
	}
	else
	{
		body_->setColor(sf::Color::Magenta);
	}

	switch (type_)
	{
	case rock_solid:
		switch (usage_)
		{
		case land:
			break;
		case wall:
			break;
		default:
			break;
		}
		break;
	case liquid:
		switch (usage_)
		{
		case land:
			break;
		case wall:
			break;
		default:
			break;
		}
		break;
	case gas:
		switch (usage_)
		{
		case land:
			break;
		case wall:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

tile::tile(tile* other)
{
}

std::shared_ptr<sf::Sprite> tile::get_body() const
{
	return body_;
}

bool tile::is_visible() const
{
	return appearance_ == visible;
}

void tile::set_tile_level(const unsigned int tile_level)
{
	tile_level_ = tile_level;
}

const unsigned int tile::get_tile_level() const
{
	return tile_level_;
}
