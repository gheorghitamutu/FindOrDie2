#pragma once
#include <SFML/Graphics.hpp>

#include<Windows.h>
#include<Xinput.h>

#include<string>

enum InputKeys
{
	Up,
	Down,
	Left,
	Right,
	C		// (un)focus camera on player
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

	void Update();

	void AddAction(int id, sf::Keyboard::Key key);
	bool IsKeyPressed(int id);
	bool IsKeyReleased(int id, sf::Event* event);

	bool IsButtonPressed(WORD button); // controller button

	sf::Vector2f GetThumbStickLeft(); // controller thumb
	sf::Vector2f GetThumbStickRight(); // controller thumb
private:
	std::map<int, sf::Keyboard::Key> m_Actions;

	XINPUT_STATE m_CurrentState; // controller state
};

