#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace ge
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);
		~PauseState();

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataRef m_Data;

		sf::Clock m_Clock;

		sf::Sprite m_ResumeButton;
		sf::Text m_ResumeButtonText;

		sf::Sprite m_SaveButton;
		sf::Text m_SaveButtonText;

		sf::Sprite m_ExitButton;
		sf::Text m_ExitButtonText;

		sf::Color m_Gray = sf::Color(128, 128, 128);
	};
}
