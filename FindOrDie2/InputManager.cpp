#include "InputManager.hpp"

namespace ge
{
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
	bool InputManager::IsSpriteClicked(sf::Sprite * pObject, sf::Mouse::Button button, sf::RenderWindow * pWindow)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			auto objectPosition = pObject->getPosition();
			auto objectGlobalBounds = pObject->getGlobalBounds();
			sf::IntRect buttonRect(
				(int)objectPosition.x, 
				(int)objectPosition.y, 
				(int)objectGlobalBounds.width, 
				(int)objectGlobalBounds.height);
			
			if (buttonRect.contains(sf::Mouse::getPosition(*pWindow)))
			{
				return true;
			}
		}

		return false;
	}
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow * pWindow)
	{
		return sf::Mouse::getPosition(*pWindow);
	}
}