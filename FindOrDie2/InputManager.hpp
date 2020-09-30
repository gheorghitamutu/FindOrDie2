#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace ge
{
	enum input_keys
	{
		up,
		down,
		left,
		right,
		c,		// (un)focus camera on player
		esc		// switch states 
	};

	class input_manager
	{
	public:
		input_manager() noexcept;

		input_manager(const input_manager& other) = default;
		input_manager(input_manager&& other) noexcept = default;
		input_manager& operator=(const input_manager& other) = default;
		input_manager& operator=(input_manager&& other) noexcept = default;

		~input_manager() = default;

		void add_action(int id, sf::Keyboard::Key key);
		bool is_key_pressed(int id);
		bool is_key_released(int id, const std::shared_ptr<sf::Event>& event);

		bool is_sprite_clicked(sf::Sprite& object, sf::Mouse::Button button, const std::shared_ptr<sf::RenderWindow>& p_window) const;
		
		sf::Vector2i get_mouse_position(const std::unique_ptr<sf::RenderWindow> p_window) const;

	private:
		std::map<int, sf::Keyboard::Key> actions_;
	};
}