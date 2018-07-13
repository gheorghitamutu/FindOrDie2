#pragma once
#include <SFML/Graphics.hpp>


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
	sf::RectangleShape m_Rect;
};

