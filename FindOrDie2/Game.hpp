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

	enum GameState
	{
		MainMenu,
		CharacterSelection,
		Running,
		Pause,
		Exit
	};

	class Game
	{
	public:
		Game() noexcept;
		~Game();

	public:
		static const unsigned int windowHeight = 1920;
		static const unsigned int windowWidth = 1080;

	private:
		void Run();

		bool ProcessEvents();
		void Update(float deltaTime);
		void Draw();

	private:
		Player* m_pPlayer = nullptr;

		sf::View *m_pDefaultView = nullptr;
		sf::View *m_pCurrentView = nullptr;

		std::string m_GameTitle = "FindOrDie2";

		Map* m_pMap = nullptr;

		GameState m_CurrentGameState = GameState::Running;
		unsigned int m_MaxFPS = 60;

		const float m_DeltaTime = 1.0f / 60.0f;

		sf::Clock m_Clock;

		GameDataRef m_Data = std::make_shared<GameData>();
	};
}

