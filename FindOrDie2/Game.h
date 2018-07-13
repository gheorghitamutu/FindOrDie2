#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();
	void Run();

public:
	static const unsigned int windowHeight = 800;
	static const unsigned int windowWidth = 600;

private:
	bool ProcessEvents();
	void Update(float deltaTime);
	void Draw();

private:
	sf::RenderWindow* m_pWindow = nullptr;

	Player* m_pPlayer = nullptr;

	sf::View *m_pDefaultView = nullptr;
	sf::View *m_pCurrentView = nullptr;

	std::string m_WindowTitle = "Game";

	Map* m_pMap = nullptr;
};

