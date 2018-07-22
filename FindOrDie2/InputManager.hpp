#pragma once

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

enum InputKeys
{
	Up,
	Down,
	Left,
	Right,
	C,		// (un)focus camera on player
	Esc		// switch states 
};

class InputManager
{
private:
	InputManager() noexcept;

public:
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}
	~InputManager();

	void Update();

	void AddAction(int id, sf::Keyboard::Key key);
	bool IsKeyPressed(int id);
	bool IsKeyReleased(int id, sf::Event* event);

private:
	std::map<int, sf::Keyboard::Key> m_Actions;
};

