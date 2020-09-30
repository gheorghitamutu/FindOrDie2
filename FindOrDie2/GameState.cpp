#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"

#include <iostream>
#include "Player.hpp"

namespace ge
{
	game_state::game_state(std::shared_ptr<ge::game_context> data) :
		data_(data), 
		game_progress_(game_progress::playing)
	{
	}

	void game_state::init()
	{
		p_map_ = std::make_shared<map>(map(data_));

		data_->input_manager_->add_action(up, sf::Keyboard::Key::Up);
		data_->input_manager_->add_action(down, sf::Keyboard::Key::Down);
		data_->input_manager_->add_action(left, sf::Keyboard::Key::Left);
		data_->input_manager_->add_action(right, sf::Keyboard::Key::Right);
		data_->input_manager_->add_action(c, sf::Keyboard::Key::C);
		data_->input_manager_->add_action(esc, sf::Keyboard::Key::Escape);

		const auto window_size = data_->render_window_->getSize();

		data_->camera_->set_current_view_size({ static_cast<float>(window_size.x), static_cast<float>(window_size.y) });
		data_->camera_->zoom(0.0f);
		data_->camera_->set_current_view_center({ 0,0 });

		p_player_ = std::make_shared<player>(player(data_));

		p_map_->generate_map();
	}

	void game_state::handle_input()
	{
		sf::Event event{};
		while (data_->render_window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				data_->render_window_->close();
			}

			switch (game_progress_)
			{
			case game_progress::playing:
					p_player_->process_events(std::make_shared<sf::Event>(event));

					if (data_->input_manager_->is_key_released(esc, std::make_shared<sf::Event>(event)))
					{
						std::wcout << "Switch from in-game to pause screen!" << std::endl;
						data_->machine_->add_state(std::make_shared<pause_state>(pause_state(data_)), false);
					}

					if (event.type == sf::Event::MouseWheelMoved)
					{
						data_->camera_->zoom(event.mouseWheel.delta * 0.1f);
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
			if (data_->camera_->is_camera_dragged())
			{
				p_player_->set_focus(false);
			}
			p_player_->update(delta_time);
			p_map_->update();
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
		data_->camera_->reset();

		switch (game_progress_)
		{
		case game_progress::playing:
			p_map_->draw();
			p_player_->draw();
			break;
		case game_progress::pause:
			// ...
			break;
		default:
			break;
		}

		data_->camera_->flush();
	}

	void game_state::pause()
	{
	}

	void game_state::resume()
	{
	}
}
