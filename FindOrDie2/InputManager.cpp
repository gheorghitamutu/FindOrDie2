#include "InputManager.hpp"

namespace ge
{
	input_manager::input_manager() noexcept
	{
	}

	void input_manager::add_action(const int id, const sf::Keyboard::Key key)
	{
		actions_[id] = key;
	}

	bool input_manager::is_key_pressed(const int id)
	{
		return sf::Keyboard::isKeyPressed(actions_[id]);
	}

	bool input_manager::is_key_released(const int id, const std::shared_ptr<sf::Event>& event)
	{
		if (event->type == sf::Event::KeyReleased)
		{
			return event->key.code == actions_[id];
		}

		return false;
	}
	bool input_manager::is_sprite_clicked(sf::Sprite& object, const sf::Mouse::Button button, const std::shared_ptr<sf::RenderWindow>& p_window) const
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			const auto object_position = object.getPosition();
			const auto object_global_bounds = object.getGlobalBounds();
			sf::IntRect button_rect(
				static_cast<int>(object_position.x), 
				static_cast<int>(object_position.y), 
				static_cast<int>(object_global_bounds.width), 
				static_cast<int>(object_global_bounds.height));
			
			if (button_rect.contains(sf::Mouse::getPosition(*p_window)))
			{
				return true;
			}
		}

		return false;
	}
	sf::Vector2i input_manager::get_mouse_position(const std::unique_ptr<sf::RenderWindow> p_window) const
	{
		return sf::Mouse::getPosition(*p_window);
	}
}