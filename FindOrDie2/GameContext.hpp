#pragma once

#include <memory>
#include <iostream>

#include "DEFINITIONS.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "SplashState.hpp"

namespace ge
{
	class game_context
	{
	public:
		std::shared_ptr<state_machine> machine_;
		std::shared_ptr<sf::RenderWindow> render_window_;
		std::shared_ptr<asset_manager> asset_manager_;
		std::shared_ptr<input_manager> input_manager_;
		std::shared_ptr<camera> camera_;
		std::shared_ptr<player> player_;
		std::shared_ptr<map> map_;


		game_context();

		game_context(const game_context& other) = delete;
		game_context(game_context&& other) noexcept = default;
		game_context(game_context* other) = delete;
		game_context& operator=(const game_context& other) = delete;
		game_context& operator=(game_context&& other) noexcept = delete;

		~game_context() = default;
	};
}

