#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Map.hpp"

namespace ge
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState();

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataRef m_Data;

		sf::Clock m_Clock;

		Map *m_pMap = nullptr;

		Player *m_pPlayer = nullptr;

		sf::View *m_pDefaultView = nullptr;
		sf::View *m_pCurrentView = nullptr;

		int m_GameState;
	};
}
