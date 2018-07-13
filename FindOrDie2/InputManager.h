#pragma once
#include <SFML/Graphics.hpp>


enum InputKeys
{
	Up,
	Down,
	Left,
	Right
};

class InputManager
{
private:
	InputManager();

public:
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}
	~InputManager();

	void AddAction(int id, sf::Keyboard::Key key);
	bool IsActionTriggered(int id);

private:
	std::map<int, sf::Keyboard::Key> m_Actions;
};

