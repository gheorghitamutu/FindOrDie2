#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::CleanUp()
{
	for (auto tile : m_Tiles)
	{
		delete tile;
		tile = nullptr;
	}
}

void Map::GenerateMap()
{

	sf::Sprite* tile = nullptr;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			tile = new sf::Sprite();
			tile->setOrigin({ tileSize / 2, tileSize / 2 });
			// flat surface formula
			tile->setPosition({ j * 32.0f, i * 16.0f + j * 16.0f });
			tile->setTexture(*ResourceManager::GetInstance()->RequestTexture("Tiles"));
			tile->setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));

			m_Tiles.emplace_back(tile);
		}
	}
}

void Map::Draw(sf::RenderWindow * pWindow)
{
	for (auto tile : m_Tiles)
	{
		pWindow->draw(*tile);
	}
}
