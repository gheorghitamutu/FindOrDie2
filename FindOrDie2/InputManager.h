#pragma once
#include <SFML/Graphics.hpp>

#include<Windows.h>
#include<Xinput.h>

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

	void Update();

	void AddAction(int id, sf::Keyboard::Key key);
	bool IsActionTriggered(int id);

	bool IsButtonPressed(WORD button); // controller

	sf::Vector2f GetThumbStickLeft();
	sf::Vector2f GetThumbStickRight();
private:
	std::map<int, sf::Keyboard::Key> m_Actions;

	XINPUT_STATE m_CurrentState; // controller state
};

