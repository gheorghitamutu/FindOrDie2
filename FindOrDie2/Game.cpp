#include "Game.hpp"

namespace ge
{
	game::game() noexcept
	{
		data_.reset(new ge::game_context());
		data_->machine_->add_state(std::make_shared<splash_state>(splash_state(data_)));
		data_->render_window_->setFramerateLimit(max_fps_);

		run();
	}

	void game::run() const
	{
		auto current_time = clock_.getElapsedTime().asSeconds();
		auto accumulator = 0.0f;

		while (data_->render_window_->isOpen())
		{
			data_->machine_->process_state_changes();

			// calculate time between events
			const auto new_time = clock_.getElapsedTime().asSeconds();
			const auto frame_time = std::min(new_time - current_time, max_frame_time);

			current_time = new_time;
			accumulator += frame_time;

			while (accumulator >= delta_time_)
			{
				data_->machine_->get_active_state()->handle_input();
				data_->machine_->get_active_state()->update(delta_time_);

				accumulator = std::max(accumulator -= delta_time_, 0.0f);
			}

			data_->machine_->get_active_state()->draw();
		}
	}
}