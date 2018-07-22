#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Map.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace ge
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(float windowWidth, float windowHeight, std::string gameTitle) noexcept;
		~Game();

	private:
		void Run();

	private:
		unsigned int m_MaxFPS = 60;

		const float m_DeltaTime = 1.0f / 60.0f;

		sf::Clock m_Clock;

		GameDataRef m_Data = std::make_shared<GameData>();
	};
}

