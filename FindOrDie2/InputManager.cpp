#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::AddAction(int id, sf::Keyboard::Key key)
{
	m_Actions[id] = key;
}

bool InputManager::IsActionTriggered(int id)
{
	return sf::Keyboard::isKeyPressed(m_Actions[id]);
}
