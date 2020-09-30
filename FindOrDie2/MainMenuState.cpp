#include <iostream>
#include <utility>

#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

namespace ge
{
	main_menu_state::main_menu_state(std::shared_ptr<game_context> data) :
		data_(data)
	{
	}

	void main_menu_state::init()
	{
		data_->asset_manager_->load_texture("Background", MAIN_MENU_BACKGROUND);
		data_->asset_manager_->load_texture("Game Title", MAIN_MENU_TITLE_BUTTON);
		data_->asset_manager_->load_texture("Play Button", MAIN_MENU_PLAY_BUTTON);
		data_->asset_manager_->load_texture("Settings Button", MAIN_MENU_SETTINGS_BUTTON);
		data_->asset_manager_->load_texture("Exit Button", MAIN_MENU_EXIT_BUTTON);
					 
		data_->asset_manager_->load_font("Main Font", MAIN_FONT);

		// background
		const auto background_texture = data_->asset_manager_->get_texture("Background");
		background_.setTexture(*background_texture);

		const auto texture_size = background_texture->getSize();
		const auto window_size = data_->render_window_->getSize();
		const auto scale_factor = sf::Vector2f(static_cast<float>(window_size.x) / texture_size.x, static_cast<float>(window_size.y) / texture_size.y);
		const auto current_scale_factor = background_.getScale();
		const auto new_scale_factor = sf::Vector2f(current_scale_factor.x * scale_factor.x, current_scale_factor.y * scale_factor.y);
		background_.scale(new_scale_factor);

		// title button
		title_button_.setTexture(*data_->asset_manager_->get_texture("Game Title"));
		title_button_.scale(new_scale_factor * 2.5f);
		const auto title_position = sf::Vector2f(
			(static_cast<float>(window_size.x) / 2) - (title_button_.getGlobalBounds().width / 2),
			(static_cast<float>(window_size.y) / 3) - (title_button_.getGlobalBounds().height / 2));
		title_button_.setPosition(title_position);

		// play button
		play_button_.setTexture(*data_->asset_manager_->get_texture("Play Button"));

		play_button_.scale(new_scale_factor * 1.5f);
		const auto play_button_position = sf::Vector2f((static_cast<float>(window_size.x) / 2) - (play_button_.getGlobalBounds().width / 2),
			(static_cast<float>(window_size.y) / 2) - (play_button_.getGlobalBounds().height / 2));
		play_button_.setPosition(play_button_position);

		// settings button
		settings_button_.setTexture(*data_->asset_manager_->get_texture("Settings Button"));

		settings_button_.scale(new_scale_factor * 1.5f);
		const auto settings_button_position = sf::Vector2f(
			play_button_position.x,
			play_button_position.y + 1.5f * play_button_.getGlobalBounds().height);
		settings_button_.setPosition(settings_button_position);

		// exit button
		exit_button_.setTexture(*data_->asset_manager_->get_texture("Exit Button"));

		exit_button_.scale(new_scale_factor * 1.5f);
		const auto exit_button_position = sf::Vector2f(
			settings_button_position.x,
			settings_button_position.y + 1.5f * settings_button_.getGlobalBounds().height);
		exit_button_.setPosition(exit_button_position);

		// set fonts and texts
		const auto main_font = data_->asset_manager_->get_font("Main Font");

		// title button text
		title_button_text_.setFont(*main_font);
		title_button_text_.setString(GAME_TITLE);
		title_button_text_.scale(new_scale_factor * 1.8f);
		title_button_text_.setFillColor(gray_);

		const auto title_text_position = sf::Vector2f(
			title_button_.getPosition().x + title_button_.getGlobalBounds().width / 2 - title_button_text_.getGlobalBounds().width / 2,
			title_button_.getPosition().y + title_button_.getGlobalBounds().height / 2 - title_button_text_.getGlobalBounds().height);
		title_button_text_.setPosition(title_text_position);

		// play button text
		play_button_text_.setFont(*main_font);
		play_button_text_.setString(MAIN_MENU_PLAY_BUTTON_TEXT);
		play_button_text_.scale(new_scale_factor * 1.5f);
		play_button_text_.setFillColor(sf::Color::White);

		const auto play_button_text_position = sf::Vector2f(
			play_button_.getPosition().x + play_button_.getGlobalBounds().width / 2 - play_button_text_.getGlobalBounds().width / 2,
			play_button_.getPosition().y + play_button_.getGlobalBounds().height / 2 - play_button_text_.getGlobalBounds().height);
		play_button_text_.setPosition(play_button_text_position);

		// settings button text
		settings_button_text_.setFont(*main_font);
		settings_button_text_.setString(MAIN_MENU_SETTINGS_BUTTON_TEXT);
		settings_button_text_.scale(new_scale_factor * 1.5f);
		settings_button_text_.setFillColor(sf::Color::White);

		const auto settings_button_text_position = sf::Vector2f(
			settings_button_.getPosition().x + settings_button_.getGlobalBounds().width / 2 - settings_button_text_.getGlobalBounds().width / 2,
			settings_button_.getPosition().y + settings_button_.getGlobalBounds().height / 2 - settings_button_text_.getGlobalBounds().height);
		settings_button_text_.setPosition(settings_button_text_position);
	
		// exit button text
		exit_button_text_.setFont(*main_font);
		exit_button_text_.setString(MAIN_MENU_EXIT_BUTTON_TEXT);
		exit_button_text_.scale(new_scale_factor * 1.5f);
		exit_button_text_.setFillColor(sf::Color::White);

		const auto exit_button_text_position = sf::Vector2f(
			exit_button_.getPosition().x + exit_button_.getGlobalBounds().width / 2 - exit_button_text_.getGlobalBounds().width / 2,
			exit_button_.getPosition().y + exit_button_.getGlobalBounds().height / 2 - exit_button_text_.getGlobalBounds().height);
		exit_button_text_.setPosition(exit_button_text_position);
	}

	void main_menu_state::handle_input()
	{
		sf::Event event{};
		while (data_->render_window_->pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->render_window_->close();
			}

			if (data_->input_manager_->is_sprite_clicked(play_button_, sf::Mouse::Left, data_->render_window_))
			{
				std::cout << "Switch to the Game Screen" << std::endl;
				data_->machine_->add_state(std::make_shared<game_state>(game_state(data_)), true);
			}

			if (data_->input_manager_->is_sprite_clicked(settings_button_, sf::Mouse::Left, data_->render_window_))
			{
				std::cout << "Switch to the Settings Screen" << std::endl;
			}

			if (data_->input_manager_->is_sprite_clicked(exit_button_, sf::Mouse::Left, data_->render_window_))
			{
				data_->render_window_->close();
			}
		}
	}

	void main_menu_state::update(const float delta_time)
	{
		// empty
	}

	void main_menu_state::draw()
	{
		data_->render_window_->clear();
					 
		data_->render_window_->draw(background_);
					 
		data_->render_window_->draw(title_button_);
		data_->render_window_->draw(title_button_text_);
					 
		data_->render_window_->draw(play_button_);
		data_->render_window_->draw(play_button_text_);
					 
		data_->render_window_->draw(settings_button_);
		data_->render_window_->draw(settings_button_text_);
					 
		data_->render_window_->draw(exit_button_);
		data_->render_window_->draw(exit_button_text_);
					 
		data_->render_window_->display();
	}

	void main_menu_state::resume()
	{
	}

	void main_menu_state::pause()
	{
	}
}
