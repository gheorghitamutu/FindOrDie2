#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace ge
{
	struct game_data
	{
		std::shared_ptr<state_machine>		machine = std::make_shared<state_machine>(state_machine());
		sf::RenderWindow*					window = nullptr;
		std::shared_ptr<asset_manager>		assets = std::make_shared<asset_manager>(asset_manager());
		std::shared_ptr<input_manager>		input = std::make_shared<input_manager>(input_manager());

		game_data() = default;

		game_data(const game_data& other) = delete;
		game_data(game_data&& other) noexcept = default;
		explicit game_data(game_data* other) {};
		game_data& operator=(const game_data& other) = delete;
		game_data& operator=(game_data&& other) noexcept = delete;

		~game_data()
		{
			delete window;
		};

	};

	enum class game_progress
	{
		playing,
		pause,
		won,
		lose,
		draw 
	};

	class game
	{
	public:
		game(float window_width, float window_height, std::string game_title) noexcept;

		game(const game& other) = default;
		game(game&& other) noexcept = default;
		game& operator=(const game& other) = delete;
		game& operator=(game&& other) noexcept = delete;

		~game() = default;

	private:
		void run() const;

		unsigned int max_fps_ = 60;

		const float delta_time_ = 1.0f / 60.0f;

		sf::Clock clock_;

		std::shared_ptr<game_data> data_ = std::make_shared<game_data>(game_data());
	};
}

