#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace ge
{
	class pause_state : public state
	{
	public:
		explicit pause_state(std::shared_ptr<game_context> data);

		pause_state(const pause_state& other) = default;
		pause_state(pause_state&& other) noexcept = default;
		pause_state& operator=(const pause_state& other) = default;
		pause_state& operator=(pause_state&& other) noexcept = default;

		~pause_state() = default;

		void init() override;

		void handle_input() override;
		void update(float delta_time) override;
		void draw() override;

		void pause() override;
		void resume() override;

	private:
		std::shared_ptr<game_context> data_;

		sf::Clock clock_;

		sf::Sprite resume_button_;
		sf::Text resume_button_text_;

		sf::Sprite save_button_;
		sf::Text save_button_text_;

		sf::Sprite exit_button_;
		sf::Text exit_button_text_;

		sf::Color gray_ = sf::Color(128, 128, 128);
	};
}
