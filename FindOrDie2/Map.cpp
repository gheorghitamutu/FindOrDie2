#include <iostream>

#include "Map.hpp"

Map::Map(ge::AssetManager* assets) noexcept
{
	m_Assets = assets;
}

Key Map::GetKey(sf::Vector2f coords)
{
	float xKey = 0;

	if (m_ViewSize.x != 0)
	{
		xKey = coords.x / m_BlockSize.x;
		
		if (xKey < 0) xKey -= 1;
		else xKey += 1;
	}

	float yKey = 0;

	if (m_ViewSize.y != 0)
	{
		yKey = coords.y / m_BlockSize.y;

		if (yKey < 0) yKey -= 1;
		else yKey += 1;
	}
	
	return { (int)(xKey), (int)(yKey) };
}

std::vector<Key> Map::GetNeighbors(Key key, unsigned int levels)
{
	std::vector<Key> blocksCoords;

	// compute lowest x and y coords
	int lowX = key.x - levels;
	int lowY = key.y - levels;

	// compute highest x and y coords
	int highX = key.x + levels;
	int highY = key.y + levels;

	// if neighbors pass from one Q to another (from Q1 to Q2, from Q3 to Q4, etc)
	// make sure you handle the transition skipping (0,0), (0,1), (1,0), (-1,0), (0,-1)
	// as the key lowest values for Qs are (1,1), (-1,1), (1,-1), (-1,-1)
	// and increase all the neighbors from that side with 1 << (0, 1) -> (1,2) >>
	
	int absX = abs(key.x) - levels;
	int absY = abs(key.y) - levels;

	if (absX <= 1 || absY <= 1)
	{
		// transition Q1 or Q4 to Q2 or Q3
		if (key.x > 0 && lowX <= 0) lowX--;

		// transition Q2 or Q3 to Q1 or Q4
		if (key.x < 0 && highX >= 0) highX++;

		// transition Q1 or Q2 to Q3 or Q4
		if (key.y > 0 && lowY <= 0)	lowY--;

		// transition Q3 or Q4 to Q1 or Q2
		if (key.y < 0 && highY >= 0) highY++;
	}


	// previously increasing the limits if transitions are happening
	// we can now ignore every pair with 0s (0,1), (1,0), (-1,0), (0,-1)
	// and add all the others
	int indexX = lowX;
	int indexY = lowY;
	for (; indexX <= highX; indexX++)
	{
		indexY = lowY;
		for (; indexY <= highY; indexY++)
		{
			Key blockKey = { indexX, indexY };
			if (indexX != 0 && indexY != 0)
					blocksCoords.emplace_back(blockKey);
		}
	}

	return blocksCoords;
}


Map::~Map()
{
	for (auto tile : m_TileBlocks)
	{
		delete tile.second;
		tile.second = nullptr;
	}
}

void Map::GenerateMap()
{

	Tile* tile = nullptr;

	for (int i = 0; i < m_MatrixTileSize; i++)
	{
		for (int j = 0; j < m_MatrixTileSize; j++)
		{
			tile = new Tile(
				"Full_Block",
				TileType::RockSolid,
				TileAppearance::Visible,
				TileUsage::Floor,
				TileState::Seen,
				m_Assets);

			tile->GetBody()->setOrigin({ tileSize / 2, tileSize / 2 });

			// flat surface formula
			auto tilePositionX = j * 32.0f;
			auto tilePositionY = i * 16.0f + j * 16.0f;
			tile->GetBody()->setPosition({ tilePositionX,  tilePositionY});

			Key tileChunkPosition = GetKey({ tilePositionX, tilePositionY });

			m_mtx.lock();

			// you lock the inserting operation in order to draw while generating the map
			{
				if (m_TileBlocks.find(tileChunkPosition) == m_TileBlocks.end())
				{
					m_TileBlocks.insert({ tileChunkPosition, new TileBlock() });
				}

				m_TileBlocks[tileChunkPosition]->GetTiles()->emplace_back(tile);
			}
			// you unlock it after you insert a tile

			m_mtx.unlock();
		}
	}
}

void Map::Draw(sf::RenderWindow * pWindow)
{
	auto viewCenter = m_pCurrentView->getCenter();

	Key chunkPosition = GetKey(viewCenter);

	std::vector<Key> chunkIndentifiers = GetNeighbors(chunkPosition, 1);

	m_mtx.lock();

	// you lock the query operation in order to draw on the screen only what's already
	// generated and required for the current view

	// you get all tiles from all blocks in the view center into one vector of tiles
	std::vector<Tile*> tiles;
	{
		for (auto &chunkId : chunkIndentifiers)
		{
			auto tileBlock = m_TileBlocks.find(chunkId);
			if (tileBlock != m_TileBlocks.end())
			{
				auto blockTiles = tileBlock->second->GetTiles();
				tiles.insert(tiles.end(), blockTiles->begin(), blockTiles->end());
			}
		}

		// then you sort the tiles in order to draw them isometric and not overlap them
		std::sort(tiles.begin(), tiles.end(), [](Tile* a, Tile* b)
		{	
			auto aBody = a->GetBody();
			auto bBody = b->GetBody();
			auto aPos = aBody->getPosition();
			auto bPos = bBody->getPosition();

			return aPos.y == bPos.y ? aPos.x > bPos.x : aPos.y < bPos.y;
		});

		// draw the sorted tiles
		for (auto tile : tiles)
		{
			pWindow->draw(*tile->GetBody());
		}
	}
	// you unlock it

	m_mtx.unlock();
}

void Map::SetView(sf::View * pView)
{
	m_pCurrentView = pView;

	m_ViewSize = m_pCurrentView->getSize();

	// tiles contained by a block relative to view size and tile size
	m_BlockMaxTiles = { 
		(m_ViewSize.x == 0) ? 0 : (int)(m_ViewSize.x / tileSize / 2),
		(m_ViewSize.x == 0) ? 0 : (int)(m_ViewSize.y / tileSize / 2) };

	// block size relative to view size (1/4 view size)
	m_BlockSize = { 
		(m_ViewSize.x == 0) ? 0 : (int)(m_ViewSize.x / 2),
		(m_ViewSize.y == 0) ? 0 : (int)(m_ViewSize.y / 2) };
}
