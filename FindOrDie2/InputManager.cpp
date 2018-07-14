#include "stdafx.h"
#include "InputManager.h"
#include <minwinbase.h>


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
}

void InputManager::AddAction(int id, sf::Keyboard::Key key)
{
	m_Actions[id] = key;
}

bool InputManager::IsKeyPressed(int id)
{
	return sf::Keyboard::isKeyPressed(m_Actions[id]);
}

bool InputManager::IsKeyReleased(int id, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
		return event->key.code == m_Actions[id];

	return false;
}

bool InputManager::IsButtonPressed(WORD button)
{
	return (m_CurrentState.Gamepad.wButtons & button) != 0;
}

sf::Vector2f InputManager::GetThumbStickLeft()
{
	sf::Vector2f result;

	result.x = m_CurrentState.Gamepad.sThumbLX;
	result.y = -float(m_CurrentState.Gamepad.sThumbLY); // reverted in SFML

	result.x /= 32768.0f; // documentation for XINPUT requires it
	result.y /= 32768.0f; // documentation for XINPUT requires it

	if (abs(result.x) < 0.19f) result.x = 0; // don't always move, set a ~deadzone
	if (abs(result.y) < 0.19f) result.y = 0; // don't always move, set a ~deadzone

	return result;
}

sf::Vector2f InputManager::GetThumbStickRight()
{
	sf::Vector2f result;

	result.x = m_CurrentState.Gamepad.sThumbRX;
	result.y = -float(m_CurrentState.Gamepad.sThumbRY); // reverted in SFML

	result.x /= 32768.0f; // documentation for XINPUT requires it
	result.y /= 32768.0f; // documentation for XINPUT requires it

	if (abs(result.x) < 0.19f) result.x = 0; // don't always move, set a ~deadzone
	if (abs(result.y) < 0.19f) result.y = 0; // don't always move, set a ~deadzone

	return result;
}
