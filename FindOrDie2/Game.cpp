#include "Game.hpp"
#include "SplashState.hpp"

namespace ge
{
	game::game(const float window_width, const float window_height, const std::string game_title) noexcept
	{
		data_->window.reset(		
				new sf::RenderWindow(
				sf::VideoMode(
					static_cast<unsigned int>(window_width), 
					static_cast<unsigned int>(window_height)),
				game_title,
				sf::Style::Close | sf::Style::Titlebar));

		data_->machine->add_state(std::make_shared<splash_state>(splash_state(data_)));

		data_->window->setFramerateLimit(max_fps_);

		run();
	}

	void game::run() const
	{
		auto current_time = clock_.getElapsedTime().asSeconds();
		auto accumulator = 0.0f;

		while (data_->window->isOpen())
		{
			data_->machine->process_state_changes();

			// calculate time between events
			const auto new_time = clock_.getElapsedTime().asSeconds();
			auto frame_time = new_time - current_time;

			if (frame_time > 0.25f)
			{
				frame_time = 0.25f;
			}

			current_time = new_time;
			accumulator += frame_time;

			while (accumulator >= delta_time_)
			{
				data_->machine->get_active_state()->handle_input();
				data_->machine->get_active_state()->update(delta_time_);

				accumulator -= delta_time_;
			}
			data_->machine->get_active_state()->draw();
		}
	}
}