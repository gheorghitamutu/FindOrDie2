#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Player.hpp"

namespace ge
{
	class game_state : public state
	{
	public:
		explicit game_state(std::shared_ptr<game_data> data);

		game_state(const game_state& other) = default;
		game_state(game_state&& other) noexcept = default;
		game_state& operator=(const game_state& other) = default;
		game_state& operator=(game_state&& other) noexcept = default;

		~game_state() = default;

		void init() override;

		void handle_input() override;
		void update(float delta_time) override;
		void draw() override;

		void pause() override;
		void resume() override;
	private:
		std::shared_ptr<game_data> data_;

		sf::Clock clock_;

		std::shared_ptr<map> p_map_;

		std::shared_ptr<player> p_player_;

		std::shared_ptr<sf::View> p_default_view_;
		std::shared_ptr<sf::View> p_current_view_;

		game_progress game_progress_;
	};
};
