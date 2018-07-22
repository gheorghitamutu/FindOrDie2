#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "DEFINITIONS.hpp"
#include "GameState.h"

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
		m_Data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_BUTTON);
		m_Data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		m_Data->assets.LoadTexture("Settings Button", MAIN_MENU_SETTINGS_BUTTON);
		m_Data->assets.LoadTexture("Exit Button", MAIN_MENU_EXIT_BUTTON);

		m_Data->assets.LoadFont("Main Font", MAIN_FONT);

		// background
		auto backgroundTexture = m_Data->assets.GetTexture("Background");
		m_Background.setTexture(*backgroundTexture);

		auto textureSize = backgroundTexture->getSize();
		auto scaleFactor = sf::Vector2f((float)SCREEN_WIDTH / textureSize.x, (float)SCREEN_HEIGHT / textureSize.y);
		auto currentScaleFactor = m_Background.getScale();
		auto newScaleFactor = sf::Vector2f(currentScaleFactor.x * scaleFactor.x, currentScaleFactor.y * scaleFactor.y);
		m_Background.scale(newScaleFactor);

		// title button
		m_TitleButton.setTexture(*m_Data->assets.GetTexture("Game Title"));
		m_TitleButton.scale(newScaleFactor * 2.5f);
		auto titlePosition = sf::Vector2f(
			(SCREEN_WIDTH / 2) - (m_TitleButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 3) - (m_TitleButton.getGlobalBounds().height / 2));
		m_TitleButton.setPosition(titlePosition);

		// play button
		m_PlayButton.setTexture(*m_Data->assets.GetTexture("Play Button"));

		m_PlayButton.scale(newScaleFactor * 1.5f);
		auto playButtonPosition = sf::Vector2f((SCREEN_WIDTH / 2) - (m_PlayButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (m_PlayButton.getGlobalBounds().height / 2));
		m_PlayButton.setPosition(playButtonPosition);

		// settings button
		m_SettingsButton.setTexture(*m_Data->assets.GetTexture("Settings Button"));

		m_SettingsButton.scale(newScaleFactor * 1.5f);
		auto settingsButtonPosition = sf::Vector2f(
			playButtonPosition.x,
			playButtonPosition.y + 1.5f * m_PlayButton.getGlobalBounds().height);
		m_SettingsButton.setPosition(settingsButtonPosition);

		// exit button
		m_ExitButton.setTexture(*m_Data->assets.GetTexture("Exit Button"));

		m_ExitButton.scale(newScaleFactor * 1.5f);
		auto exitButtonPosition = sf::Vector2f(
			settingsButtonPosition.x,
			settingsButtonPosition.y + 1.5f * m_SettingsButton.getGlobalBounds().height);
		m_ExitButton.setPosition(exitButtonPosition);

		// set fonts and texts
		auto mainFont = m_Data->assets.GetFont("Main Font");

		// title button text
		m_TitleButtonText.setFont(*mainFont);
		m_TitleButtonText.setString(GAME_TITLE);
		m_TitleButtonText.scale(newScaleFactor * 1.8f);
		m_TitleButtonText.setFillColor(m_Gray);
	
		auto titleTextPosition = sf::Vector2f(
			m_TitleButton.getPosition().x + m_TitleButton.getGlobalBounds().width / 2 - m_TitleButtonText.getGlobalBounds().width / 2,
			m_TitleButton.getPosition().y + m_TitleButton.getGlobalBounds().height / 2 - m_TitleButtonText.getGlobalBounds().height);
		m_TitleButtonText.setPosition(titleTextPosition);

		// play button text
		m_PlayButtonText.setFont(*mainFont);
		m_PlayButtonText.setString(MAIN_MENU_PLAY_BUTTON_TEXT);
		m_PlayButtonText.scale(newScaleFactor * 1.5f);
		m_PlayButtonText.setFillColor(sf::Color::White);

		auto playButtonTextPosition = sf::Vector2f(
			m_PlayButton.getPosition().x + m_PlayButton.getGlobalBounds().width / 2 - m_PlayButtonText.getGlobalBounds().width / 2,
			m_PlayButton.getPosition().y + m_PlayButton.getGlobalBounds().height / 2 - m_PlayButtonText.getGlobalBounds().height);
		m_PlayButtonText.setPosition(playButtonTextPosition);

		// settings button text
		m_SettingsButtonText.setFont(*mainFont);
		m_SettingsButtonText.setString(MAIN_MENU_SETTINGS_BUTTON_TEXT);
		m_SettingsButtonText.scale(newScaleFactor * 1.5f);
		m_SettingsButtonText.setFillColor(sf::Color::White);

		auto settingsButtonTextPosition = sf::Vector2f(
			m_SettingsButton.getPosition().x + m_SettingsButton.getGlobalBounds().width / 2 - m_SettingsButtonText.getGlobalBounds().width / 2,
			m_SettingsButton.getPosition().y + m_SettingsButton.getGlobalBounds().height / 2 - m_SettingsButtonText.getGlobalBounds().height);
		m_SettingsButtonText.setPosition(settingsButtonTextPosition);
	
		// exit button text
		m_ExitButtonText.setFont(*mainFont);
		m_ExitButtonText.setString(MAIN_MENU_EXIT_BUTTON_TEXT);
		m_ExitButtonText.scale(newScaleFactor * 1.5f);
		m_ExitButtonText.setFillColor(sf::Color::White);

		auto exitButtonTextPosition = sf::Vector2f(
			m_ExitButton.getPosition().x + m_ExitButton.getGlobalBounds().width / 2 - m_ExitButtonText.getGlobalBounds().width / 2,
			m_ExitButton.getPosition().y + m_ExitButton.getGlobalBounds().height / 2 - m_ExitButtonText.getGlobalBounds().height);
		m_ExitButtonText.setPosition(exitButtonTextPosition);
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
				m_Data->machine.AddState(StateRef(new GameState(m_Data)), true);
			}

			if (m_Data->input.IsSpriteClicked(&m_SettingsButton, sf::Mouse::Left, &m_Data->window))
			{
				std::cout << "Switch to the Settings Screen" << std::endl;
			}

			if (m_Data->input.IsSpriteClicked(&m_ExitButton, sf::Mouse::Left, &m_Data->window))
			{
				m_Data->window.close();
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

		m_Data->window.draw(m_TitleButton);
		m_Data->window.draw(m_TitleButtonText);

		m_Data->window.draw(m_PlayButton);
		m_Data->window.draw(m_PlayButtonText);

		m_Data->window.draw(m_SettingsButton);
		m_Data->window.draw(m_SettingsButtonText);

		m_Data->window.draw(m_ExitButton);
		m_Data->window.draw(m_ExitButtonText);

		m_Data->window.display();
	}
}