#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "ResourceManager.h"

class Map
{
private:
	Map();

public:
	static Map* GetInstance()
	{
		static Map instance;
		return &instance;
	}
	~Map();

	void CleanUp();
	void GenerateMap();
	void Draw(sf::RenderWindow* pWindow);
	void SetView(sf::View* pView);

public:
	static const unsigned int tileSize = 64;

private:
	std::vector<sf::Sprite*> m_Tiles;
	sf::View* m_pCurrentView = nullptr; // no view created here, do not free it
	unsigned long long m_MatrixTileSize = 2000;
};

