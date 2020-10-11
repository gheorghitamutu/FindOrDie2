#pragma once

#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "GameState.hpp"

namespace ge
{
	class main_menu_state : public state
	{
	public:
		explicit main_menu_state(std::shared_ptr<class game_context>& data);

		main_menu_state(const main_menu_state& other) = default;
		main_menu_state(main_menu_state&& other) noexcept = default;
		main_menu_state& operator=(const main_menu_state& other) = default;
		main_menu_state& operator=(main_menu_state&& other) noexcept = default;

		~main_menu_state() = default;

		void init() override;

		void handle_input() override;
		void update(float delta_time) override;
		void draw() override;

		void resume() override;
		void pause() override;

	private:
		std::shared_ptr<game_context> data_;

		sf::Sprite background_;

		sf::Sprite title_button_;
		sf::Text title_button_text_;
		
		sf::Sprite play_button_;
		sf::Text play_button_text_;

		sf::Sprite settings_button_;
		sf::Text settings_button_text_;

		sf::Sprite exit_button_;
		sf::Text exit_button_text_;

		sf::Color gray_ = sf::Color(128, 128, 128);
	};
}
