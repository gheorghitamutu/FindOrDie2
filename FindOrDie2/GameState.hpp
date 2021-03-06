#pragma once

#include <SFML/Graphics.hpp>

#include "GameContext.hpp"
#include "State.hpp"
#include "PauseState.hpp"

namespace ge
{
	class game_state : public state
	{
	public:
		explicit game_state(std::shared_ptr<class game_context>& data);

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
		std::shared_ptr<game_context> data_;

		sf::Clock clock_;

		game_progress game_progress_;
	};
};
