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
		
		sf::Sprite m_PlayButton;

		sf::Sprite m_Title;
	};
}
