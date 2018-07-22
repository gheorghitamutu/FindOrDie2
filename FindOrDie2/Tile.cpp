#include "Tile.hpp"

Tile::Tile(std::string name, TileType type, TileAppearance appearance, TileUsage usage, TileState state, ge::AssetManager* assets)
{
	m_Body = new sf::Sprite();
	auto bodyTexture = assets->GetTexture(name);
	if (bodyTexture != nullptr)
	{
		m_Body->setTexture(*bodyTexture);
	}
	else
	{
		m_Body->setColor(sf::Color::Magenta);
	}

	m_Type = type;
	m_Appearance = appearance;
	m_Usage = usage;
	m_State = state;

	switch (m_Type)
	{
	case TileType::RockSolid:
		switch (m_Usage)
		{
		case TileUsage::Floor:
			break;
		case TileUsage::Wall:
			break;
		default:
			break;
		}
		break;
	case TileType::Liquid:
		switch (m_Usage)
		{
		case TileUsage::Floor:
			break;
		case TileUsage::Wall:
			break;
		default:
			break;
		}
		break;
	case TileType::Gas:
		switch (m_Usage)
		{
		case TileUsage::Floor:
			break;
		case TileUsage::Wall:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}


Tile::~Tile()
{
	delete m_Body;
	m_Body = nullptr;
}

sf::Sprite * Tile::GetBody()
{
	return m_Body;
}

bool Tile::IsVisible()
{
	return m_State == TileAppearance::Visible;
}
