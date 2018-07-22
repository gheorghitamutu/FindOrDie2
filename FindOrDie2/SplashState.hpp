#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace ge
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		~SplashState();

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataRef m_Data;

		sf::Clock m_Clock;

		sf::Sprite m_Background;
	};
}