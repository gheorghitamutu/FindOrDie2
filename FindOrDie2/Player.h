#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "ResourceManager.h"

class Player
{
public:
	Player();
	~Player();
	void Update(float elapsedSec);
	void Draw(sf::RenderWindow* pWindow);
	sf::Vector2f GetPosition() const;

private:
	sf::RectangleShape m_Body;
};

