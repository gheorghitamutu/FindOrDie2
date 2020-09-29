#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"

#include <iostream>
#include "Player.hpp"

namespace ge
{
	game_state::game_state(std::shared_ptr<game_data> data) :
		data_(std::move(data)), 
		game_progress_(game_progress::playing)
	{
	}

	void game_state::init()
	{
		p_map_ = std::make_shared<map>(map(data_->assets));

		data_->input->add_action(up, sf::Keyboard::Key::Up);
		data_->input->add_action(down, sf::Keyboard::Key::Down);
		data_->input->add_action(left, sf::Keyboard::Key::Left);
		data_->input->add_action(right, sf::Keyboard::Key::Right);
		data_->input->add_action(c, sf::Keyboard::Key::C);
		data_->input->add_action(esc, sf::Keyboard::Key::Escape);

		const auto window_size = data_->window->getSize();

		p_default_view_ = std::make_shared<sf::View>(sf::View());
		p_default_view_->setSize({ static_cast<float>(window_size.x), static_cast<float>(window_size.y) });
		p_default_view_->zoom(1.0f);
		p_default_view_->setCenter({ 0,0 });

		p_current_view_ = p_default_view_;

		p_player_ = std::make_shared<player>(player(data_));
		p_current_view_ = p_player_->get_view();

		p_map_->set_view(p_current_view_);

		p_map_->generate_map();
	}

	void game_state::handle_input()
	{
		sf::Event event{};
		while (data_->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				data_->window->close();
			}

			switch (game_progress_)
			{
			case game_progress::playing:
					p_player_->process_events(std::make_shared<sf::Event>(event));

					if (data_->input->is_key_released(esc, std::make_shared<sf::Event>(event)))
					{
						std::wcout << "Switch from in-game to pause screen!" << std::endl;
						data_->machine->add_state(std::make_shared<pause_state>(pause_state(data_)), false);
					}
					break;
			case game_progress::pause:
					// ..
					break;
				default:
					break;
			}
		}
	}

	void game_state::update(const float delta_time)
	{
		switch (game_progress_)
		{
		case game_progress::playing:
			p_player_->update(delta_time);
			break;
		case game_progress::pause:
			// ...
			break;
		default:
			break;
		}
	}

	void game_state::draw()
	{
		data_->window->clear();
		data_->window->setView(*p_current_view_);

		switch (game_progress_)
		{
		case game_progress::playing:
			p_map_->draw(data_->window);
			p_player_->draw(data_->window);
			break;
		case game_progress::pause:
			// ...
			break;
		default:
			break;
		}

		data_->window->display();
	}

	void game_state::pause()
	{
	}

	void game_state::resume()
	{
	}
}
