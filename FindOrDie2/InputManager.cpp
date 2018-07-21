#include "InputManager.h"


InputManager::InputManager() noexcept
{
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
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
