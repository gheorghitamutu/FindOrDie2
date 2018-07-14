#include "stdafx.h"
#include "Map.h"
#include <iostream>


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
	m_Tiles.reserve(m_MatrixTileSize);

	for (int i = 0; i < m_MatrixTileSize; i++)
	{
		for (int j = 0; j < m_MatrixTileSize; j++)
		{
			tile = new sf::Sprite();
			tile->setOrigin({ tileSize / 2, tileSize / 2 });
			// flat surface formula
			tile->setPosition({ j * 32.0f, i * 16.0f + j * 16.0f });
			tile->setTexture(*ResourceManager::GetInstance()->RequestTexture("Surface_Left"));
			tile->setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));

			m_Tiles.emplace_back(tile);
		}
	}
}

void Map::Draw(sf::RenderWindow * pWindow)
{
	auto viewCenter = m_pCurrentView->getCenter();
	auto viewSize = m_pCurrentView->getSize();

	sf::FloatRect rectBounds;
	rectBounds.left = viewCenter.x - viewSize.x / 2.f;
	rectBounds.top = viewCenter.y - viewSize.y / 2.f;
	rectBounds.width = viewSize.x;
	rectBounds.height = viewSize.y;

	for (auto tile : m_Tiles)
	{
		if (tile->getGlobalBounds().intersects(rectBounds))
			pWindow->draw(*tile);
	}
}

void Map::SetView(sf::View * pView)
{
	m_pCurrentView = pView;
}
