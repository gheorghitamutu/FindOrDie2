#include <memory>
#include <iostream>
#include <utility>

#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

namespace ge
{
	splash_state::splash_state(const std::shared_ptr<game_data>& data) :
		data_(data)
	{
	}

	void splash_state::init()
	{
		data_->assets->load_texture(
			"Splash State Background", 
			SPLASH_BACKGROUND);

		const auto texture = data_->assets->get_texture("Splash State Background");
		background_.setTexture(*texture);

		const auto window_size = data_->window->getSize();

		// resize the background to fit any resolution
		const auto texture_size = texture->getSize();
		const auto scale_factor = sf::Vector2f(static_cast<float>(window_size.x) / texture_size.x, static_cast<float>(window_size.y) / texture_size.y);
		const auto current_scale_factor = background_.getScale();
		const auto new_scale_factor = sf::Vector2f(current_scale_factor.x * scale_factor.x, current_scale_factor.y * scale_factor.y);
		background_.scale(new_scale_factor);
	}

	void splash_state::handle_input()
	{
		sf::Event event{};

		while (data_->window->pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->window->close();
			}
		}
	}

	void splash_state::update(const float delta_time)
	{
		if (clock_.getElapsedTime().asSeconds() > SPLASH_TIMEOUT)
		{
			// Switch to the Main Menu
			std::cout << "Switch to the Main Menu" << std::endl;
			data_->machine->add_state(std::make_shared<main_menu_state>(main_menu_state(data_)), true);
		}
	}

	void splash_state::draw()
	{
		data_->window->clear(sf::Color::Black);

		data_->window->draw(background_);

		data_->window->display();
	}

	void splash_state::pause()
	{
	}

	void splash_state::resume()
	{
	}
}
