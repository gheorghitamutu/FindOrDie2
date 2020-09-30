#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace ge
{
	class splash_state : public state
	{
	public:
		explicit splash_state(const std::shared_ptr<game_context>& data);

		splash_state(const splash_state& other) = default;
		splash_state(splash_state&& other) noexcept = default;
		splash_state& operator=(const splash_state& other) = default;
		splash_state& operator=(splash_state&& other) noexcept = default;

		~splash_state() = default;

		void init() override;

		void handle_input() override;
		void update(float delta_time) override;
		void draw() override;

		void pause() override;
		void resume() override;

	private:
		std::shared_ptr<game_context> data_;

		sf::Clock clock_;

		sf::Sprite background_;
	};
}