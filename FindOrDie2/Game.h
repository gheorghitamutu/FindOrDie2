#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	bool ProcessEvents();
	void Update(float deltaTime);
	void Draw();

private:
	sf::RenderWindow* m_pWindow = nullptr;

	Player* m_pPlayer = nullptr;

	sf::View m_View;
};

