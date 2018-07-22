#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "AssetManager.hpp"

enum TileType
{
	RockSolid,
	Liquid,
	Gas
};

enum TileAppearance
{
	Visible,
	Invisible
};

enum TileUsage
{
	Floor,
	Wall
};

enum TileState
{
	Seen,
	Hidden
};

class Tile
{
public:
	Tile(std::string name, TileType type, TileAppearance appearance, TileUsage usage, TileState state);
	~Tile();
	sf::Sprite* GetBody();
	bool IsVisible();

private:
	sf::Sprite* m_Body = nullptr;
	std::vector<float> m_CollisionPoints;

	TileType m_Type = TileType::RockSolid;
	TileAppearance m_Appearance = TileAppearance::Visible;
	TileUsage m_Usage = TileUsage::Floor;
	TileState m_State = TileState::Seen;
};

