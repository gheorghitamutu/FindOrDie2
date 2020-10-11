#include "Tile.hpp"

tile::tile(const std::shared_ptr<sf::Texture>& texture, const tile_type type, const tile_appearance appearance,
           const tile_usage usage, const unsigned int tile_level) :
	type_(type),
	appearance_(appearance),
	usage_(usage),
	tile_level_(tile_level)
{
	body_ = std::make_shared<sf::Sprite>(sf::Sprite());
		
	if (texture != nullptr)
	{
		body_->setTexture(*texture);
	}
	else
	{
		body_->setColor(sf::Color::Magenta);
	}

	switch (type_)
	{
	case tile_type::rock_solid:
		switch (usage_)
		{
		case tile_usage::land:
			break;
		case tile_usage::wall:
			break;
		default:
			break;
		}
		break;
	case tile_type::liquid:
		switch (usage_)
		{
		case tile_usage::land:
			break;
		case tile_usage::wall:
			break;
		default:
			break;
		}
		break;
	case tile_type::gas:
		switch (usage_)
		{
		case tile_usage::land:
			break;
		case tile_usage::wall:
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
	return appearance_ == tile_appearance::visible;
}

void tile::set_tile_level(const unsigned int tile_level)
{
	tile_level_ = tile_level;
}

const unsigned int tile::get_tile_level() const
{
	return tile_level_;
}

const tile_appearance tile::get_tile_appearance() const
{
	return appearance_;
}
