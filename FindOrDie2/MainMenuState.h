#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace ge
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState();

		void Init();

		void HandleInput();
		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataRef m_Data;

		sf::Sprite m_Background;

		sf::Sprite m_TitleButton;
		sf::Text m_TitleButtonText;
		
		sf::Sprite m_PlayButton;
		sf::Text m_PlayButtonText;

		sf::Sprite m_SettingsButton;
		sf::Text m_SettingsButtonText;

		sf::Sprite m_ExitButton;
		sf::Text m_ExitButtonText;

		sf::Color m_Gray = sf::Color(128, 128, 128);
	};
}
