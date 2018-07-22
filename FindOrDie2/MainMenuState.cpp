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

		m_Data->assets.LoadFont("Main Font", MAIN_MENU_FONT);

		auto backgroundTexture = m_Data->assets.GetTexture("Background");
		m_Background.setTexture(*backgroundTexture);

		// resize the background to fit any resolution
		auto textureSize = backgroundTexture->getSize();
		auto scaleFactor = sf::Vector2f((float)SCREEN_WIDTH / textureSize.x, (float)SCREEN_HEIGHT / textureSize.y);
		auto currentScaleFactor = m_Background.getScale();
		auto newScaleFactor = sf::Vector2f(currentScaleFactor.x * scaleFactor.x, currentScaleFactor.y * scaleFactor.y);
		m_Background.scale(newScaleFactor);

		// play button
		m_PlayButton.setTexture(*m_Data->assets.GetTexture("Play Button"));

		m_PlayButton.scale(newScaleFactor * 1.5f);
		auto playButtonPosition = sf::Vector2f((SCREEN_WIDTH / 2) - (m_PlayButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (m_PlayButton.getGlobalBounds().height / 2));
		m_PlayButton.setPosition(playButtonPosition);

		// title position
		m_Title.setTexture(*m_Data->assets.GetTexture("Game Title"));
		m_Title.scale(newScaleFactor * 2.5f);
		auto titlePosition = sf::Vector2f(
			(SCREEN_WIDTH / 2) - (m_Title.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 3) - (m_Title.getGlobalBounds().height / 2));
		m_Title.setPosition(titlePosition);

		// set fonts and texts
		auto mainFont = m_Data->assets.GetFont("Main Font");

		// title
		m_TitleText.setFont(*mainFont);
		m_TitleText.setString(GAME_TITLE);
		m_TitleText.scale(newScaleFactor * 1.8f);
		m_TitleText.setFillColor(m_Gray);
	
		auto titleTextPosition = sf::Vector2f(
			m_Title.getPosition().x + m_Title.getGlobalBounds().width / 2 - m_TitleText.getGlobalBounds().width / 2,
			m_Title.getPosition().y + m_Title.getGlobalBounds().height / 2 - m_TitleText.getGlobalBounds().height);
		m_TitleText.setPosition(titleTextPosition);

		// play button
		m_PlayButtonText.setFont(*mainFont);
		m_PlayButtonText.setString("PLAY");
		m_PlayButtonText.scale(newScaleFactor * 1.5f);
		m_PlayButtonText.setFillColor(sf::Color::White);

		auto playButtonTextPosition = sf::Vector2f(
			m_PlayButton.getPosition().x + m_PlayButton.getGlobalBounds().width / 2 - m_PlayButtonText.getGlobalBounds().width / 2,
			m_PlayButton.getPosition().y + m_PlayButton.getGlobalBounds().height / 2 - m_PlayButtonText.getGlobalBounds().height);
		m_PlayButtonText.setPosition(playButtonTextPosition);
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

		m_Data->window.draw(m_Title);
		m_Data->window.draw(m_TitleText);

		m_Data->window.draw(m_PlayButton);
		m_Data->window.draw(m_PlayButtonText);

		m_Data->window.display();
	}
}