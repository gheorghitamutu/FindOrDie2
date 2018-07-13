#pragma once
#include "SFML/Graphics.hpp"


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
};

