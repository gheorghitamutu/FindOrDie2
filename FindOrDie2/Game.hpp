#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

namespace ge
{
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
		game() noexcept;

		game(const game& other) = default;
		game(game&& other) noexcept = default;
		game& operator=(const game& other) = delete;
		game& operator=(game&& other) noexcept = delete;

		~game() = default;

	private:
		void run() const;

		const unsigned int max_fps_ = 60;

		const float delta_time_ = 1.0f / 60.0f;

		const float max_frame_time = 0.25f;

		sf::Clock clock_;

		std::shared_ptr<game_context> data_;
	};
}

