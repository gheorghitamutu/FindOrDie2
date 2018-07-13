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

public:
	static const unsigned int tileSize = 64;

private:
	std::vector<sf::Sprite*> m_Tiles;
};

