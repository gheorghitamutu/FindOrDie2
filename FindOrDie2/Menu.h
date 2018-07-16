#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
private:
	Menu() noexcept;

public:
	static Menu* GetInstance()
	{
		static Menu instance;
		return &instance;
	}
	~Menu();

	void ProcessEvents(sf::Event* event);
	void Update();
	void Draw();

};

