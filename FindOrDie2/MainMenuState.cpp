#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "DEFINITIONS.hpp"

namespace ge
{
	MainMenuState::MainMenuState(GameDataRef data) :
		m_Data(data)
	{
	}


	MainMenuState::~MainMenuState()
	{
	}

	void MainMenuState::Init()
	{
		m_Data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND);
		m_Data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		m_Data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE);

		auto backgroundTexture = m_Data->assets.GetTexture("Background");
		m_Background.setTexture(*backgroundTexture);

		// resize the background to fit any resolution
		auto textureSize = backgroundTexture->getSize();
		auto scaleFactor = sf::Vector2f((float)SCREEN_WIDTH / textureSize.x, (float)SCREEN_HEIGHT / textureSize.y);
		auto currentScaleFactor = m_Background.getScale();
		auto newScaleFactor = sf::Vector2f(currentScaleFactor.x * scaleFactor.x, currentScaleFactor.y * scaleFactor.y);
		m_Background.scale(newScaleFactor);

		m_PlayButton.setTexture(*m_Data->assets.GetTexture("Play Button"));

		// set play button position
		m_PlayButton.setPosition(
			(SCREEN_WIDTH / 2) - (m_PlayButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (m_PlayButton.getGlobalBounds().height / 2));

		m_Title.setTexture(*m_Data->assets.GetTexture("Game Title"));

		// set game title position
		m_Title.setPosition(
			(SCREEN_WIDTH / 2) - (m_Title.getGlobalBounds().width / 2),
			m_Title.getGlobalBounds().height * 0.1);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;
		while (m_Data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_Data->window.close();
			}

			if (m_Data->input.IsSpriteClicked(&m_PlayButton, sf::Mouse::Left, &m_Data->window))
			{
				std::cout << "Switch to the Game Screen" << std::endl;
			}
		}
	}

	void MainMenuState::Update(float deltaTime)
	{
		// empty
	}

	void MainMenuState::Draw(float deltaTime)
	{
		m_Data->window.clear();

		m_Data->window.draw(m_Background);
		m_Data->window.draw(m_PlayButton);
		m_Data->window.draw(m_Title);

		m_Data->window.display();
	}
}