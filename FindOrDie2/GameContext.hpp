#pragma once

#include <memory>

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "DEFINITIONS.hpp"

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


		game_context();

		game_context(const game_context& other) = delete;
		game_context(game_context&& other) noexcept = default;
		game_context(game_context* other) = delete;
		game_context& operator=(const game_context& other) = delete;
		game_context& operator=(game_context&& other) noexcept = delete;

		~game_context() = default;
	};
}

