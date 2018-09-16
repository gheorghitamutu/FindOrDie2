#include "PauseState.hpp"
#include <utility>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace ge
{
	pause_state::pause_state(std::shared_ptr<game_data> data) :
		data_(std::move(data))
	{
	}

	void pause_state::init()
	{
		data_->window->setView(data_->window->getDefaultView());
		data_->assets->load_texture("Resume Button", MAIN_MENU_RESUME_BUTTON);
		data_->assets->load_texture("Save Button", MAIN_MENU_SETTINGS_BUTTON);
		data_->assets->load_texture("Exit Button", MAIN_MENU_EXIT_BUTTON);

		data_->assets->load_font("Main Font", MAIN_FONT);

		// resume button
		resume_button_.setTexture(*data_->assets->get_texture("Resume Button"));

		// m_ResumeButton.scale(newScaleFactor * 1.5f);
		const auto resume_button_position = sf::Vector2f((static_cast<float>(SCREEN_WIDTH) / 2) - (resume_button_.getGlobalBounds().width / 2),
			(static_cast<float>(SCREEN_HEIGHT) / 3) - (resume_button_.getGlobalBounds().height / 2));
		resume_button_.setPosition(resume_button_position);

		// save button
		save_button_.setTexture(*data_->assets->get_texture("Save Button"));

		// m_SaveButton.scale(newScaleFactor * 1.5f);
		const auto save_button_position = sf::Vector2f(
			resume_button_position.x,
			resume_button_position.y + 1.5f * resume_button_.getGlobalBounds().height);
		save_button_.setPosition(save_button_position);

		// exit button
		exit_button_.setTexture(*data_->assets->get_texture("Exit Button"));

		// m_ExitButton.scale(newScaleFactor * 1.5f);
		const auto exit_button_position = sf::Vector2f(
			save_button_position.x,
			save_button_position.y + 1.5f * save_button_.getGlobalBounds().height);
		exit_button_.setPosition(exit_button_position);

		// set fonts and texts
		const auto main_font = data_->assets->get_font("Main Font");

		// resume button text
		resume_button_text_.setFont(*main_font);
		resume_button_text_.setString(MAIN_MENU_RESUME_BUTTON_TEXT);
		// m_ResumeButtonText.scale(newScaleFactor * 1.5f);
		resume_button_text_.setFillColor(sf::Color::White);

		const auto resume_button_text_position = sf::Vector2f(
			resume_button_.getPosition().x + resume_button_.getGlobalBounds().width / 2 - resume_button_text_.getGlobalBounds().width / 2,
			resume_button_.getPosition().y + resume_button_.getGlobalBounds().height / 2 - resume_button_text_.getGlobalBounds().height);
		resume_button_text_.setPosition(resume_button_text_position);

		// save button text
		save_button_text_.setFont(*main_font);
		save_button_text_.setString(MAIN_MENU_SAVE_BUTTON_TEXT);
		// m_SaveButtonText.scale(newScaleFactor * 1.5f);
		save_button_text_.setFillColor(sf::Color::White);

		const auto save_button_text_position = sf::Vector2f(
			save_button_.getPosition().x + save_button_.getGlobalBounds().width / 2 - save_button_text_.getGlobalBounds().width / 2,
			save_button_.getPosition().y + save_button_.getGlobalBounds().height / 2 - save_button_text_.getGlobalBounds().height);
		save_button_text_.setPosition(save_button_text_position);

		// exit button text
		exit_button_text_.setFont(*main_font);
		exit_button_text_.setString(MAIN_MENU_EXIT_BUTTON_TEXT);
		// m_ExitButtonText.scale(newScaleFactor * 1.5f);
		exit_button_text_.setFillColor(sf::Color::White);

		const auto exit_button_text_position = sf::Vector2f(
			exit_button_.getPosition().x + exit_button_.getGlobalBounds().width / 2 - exit_button_text_.getGlobalBounds().width / 2,
			exit_button_.getPosition().y + exit_button_.getGlobalBounds().height / 2 - exit_button_text_.getGlobalBounds().height);
		exit_button_text_.setPosition(exit_button_text_position);
	}

	void pause_state::handle_input()
	{
		sf::Event event{};
		while (data_->window->pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->window->close();
			}

			if (data_->input->is_key_released(esc, std::make_shared<sf::Event>(event)))
			{
				std::cout << "Switch to the Game Screen from PauseState" << std::endl;
				data_->machine->remove_state();
			}

			if (data_->input->is_sprite_clicked(resume_button_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Switch to the Game Screen from PauseState" << std::endl;
				data_->machine->remove_state();
			}

			if (data_->input->is_sprite_clicked(save_button_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Switch to the Save Screen from PauseState" << std::endl;
				// ..
			}

			if (data_->input->is_sprite_clicked(exit_button_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Switch to the Menu Screen from PauseState" << std::endl;
				data_->machine->remove_state();
				data_->machine->add_state(std::make_shared<main_menu_state>(main_menu_state(data_)), true);
			}
		}
	}

	void pause_state::update(const float delta_time)
	{
		// empty
	}

	void pause_state::draw()
	{
		data_->window->clear();

		data_->window->draw(resume_button_);
		data_->window->draw(resume_button_text_);

		data_->window->draw(save_button_);
		data_->window->draw(save_button_text_);

		data_->window->draw(exit_button_);
		data_->window->draw(exit_button_text_);

		data_->window->display();
	}

	void pause_state::pause()
	{
	}

	void pause_state::resume()
	{
	}
}
