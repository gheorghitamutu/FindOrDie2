#include "PauseState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.hpp"

namespace ge
{
	PauseState::PauseState(GameDataRef data) :
		m_Data(data)
	{
	}

	PauseState::~PauseState()
	{
	}

	void PauseState::Init()
	{
		m_Data->window.setView(m_Data->window.getDefaultView());
		m_Data->assets.LoadTexture("Resume Button", MAIN_MENU_RESUME_BUTTON);
		m_Data->assets.LoadTexture("Save Button", MAIN_MENU_SETTINGS_BUTTON);
		m_Data->assets.LoadTexture("Exit Button", MAIN_MENU_EXIT_BUTTON);

		m_Data->assets.LoadFont("Main Font", MAIN_FONT);

		// resume button
		m_ResumeButton.setTexture(*m_Data->assets.GetTexture("Resume Button"));

		// m_ResumeButton.scale(newScaleFactor * 1.5f);
		auto resumeButtonPosition = sf::Vector2f((SCREEN_WIDTH / 2) - (m_ResumeButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 3) - (m_ResumeButton.getGlobalBounds().height / 2));
		m_ResumeButton.setPosition(resumeButtonPosition);

		// save button
		m_SaveButton.setTexture(*m_Data->assets.GetTexture("Save Button"));

		// m_SaveButton.scale(newScaleFactor * 1.5f);
		auto saveButtonPosition = sf::Vector2f(
			resumeButtonPosition.x,
			resumeButtonPosition.y + 1.5f * m_ResumeButton.getGlobalBounds().height);
		m_SaveButton.setPosition(saveButtonPosition);

		// exit button
		m_ExitButton.setTexture(*m_Data->assets.GetTexture("Exit Button"));

		// m_ExitButton.scale(newScaleFactor * 1.5f);
		auto exitButtonPosition = sf::Vector2f(
			saveButtonPosition.x,
			saveButtonPosition.y + 1.5f * m_SaveButton.getGlobalBounds().height);
		m_ExitButton.setPosition(exitButtonPosition);

		// set fonts and texts
		auto mainFont = m_Data->assets.GetFont("Main Font");

		// resume button text
		m_ResumeButtonText.setFont(*mainFont);
		m_ResumeButtonText.setString(MAIN_MENU_RESUME_BUTTON_TEXT);
		// m_ResumeButtonText.scale(newScaleFactor * 1.5f);
		m_ResumeButtonText.setFillColor(sf::Color::White);

		auto resumeButtonTextPosition = sf::Vector2f(
			m_ResumeButton.getPosition().x + m_ResumeButton.getGlobalBounds().width / 2 - m_ResumeButtonText.getGlobalBounds().width / 2,
			m_ResumeButton.getPosition().y + m_ResumeButton.getGlobalBounds().height / 2 - m_ResumeButtonText.getGlobalBounds().height);
		m_ResumeButtonText.setPosition(resumeButtonTextPosition);

		// save button text
		m_SaveButtonText.setFont(*mainFont);
		m_SaveButtonText.setString(MAIN_MENU_SAVE_BUTTON_TEXT);
		// m_SaveButtonText.scale(newScaleFactor * 1.5f);
		m_SaveButtonText.setFillColor(sf::Color::White);

		auto saveButtonTextPosition = sf::Vector2f(
			m_SaveButton.getPosition().x + m_SaveButton.getGlobalBounds().width / 2 - m_SaveButtonText.getGlobalBounds().width / 2,
			m_SaveButton.getPosition().y + m_SaveButton.getGlobalBounds().height / 2 - m_SaveButtonText.getGlobalBounds().height);
		m_SaveButtonText.setPosition(saveButtonTextPosition);

		// exit button text
		m_ExitButtonText.setFont(*mainFont);
		m_ExitButtonText.setString(MAIN_MENU_EXIT_BUTTON_TEXT);
		// m_ExitButtonText.scale(newScaleFactor * 1.5f);
		m_ExitButtonText.setFillColor(sf::Color::White);

		auto exitButtonTextPosition = sf::Vector2f(
			m_ExitButton.getPosition().x + m_ExitButton.getGlobalBounds().width / 2 - m_ExitButtonText.getGlobalBounds().width / 2,
			m_ExitButton.getPosition().y + m_ExitButton.getGlobalBounds().height / 2 - m_ExitButtonText.getGlobalBounds().height);
		m_ExitButtonText.setPosition(exitButtonTextPosition);
	}

	void PauseState::HandleInput()
	{
		sf::Event event;
		while (m_Data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_Data->window.close();
			}

			if (m_Data->input.IsKeyReleased(ge::InputKeys::Esc, &event))
			{
				std::cout << "Switch to the Game Screen from PauseState" << std::endl;
				m_Data->machine.RemoveState();
			}

			if (m_Data->input.IsSpriteClicked(&m_ResumeButton, sf::Mouse::Left, &m_Data->window))
			{
				std::cout << "Switch to the Game Screen from PauseState" << std::endl;
				m_Data->machine.RemoveState();
			}

			if (m_Data->input.IsSpriteClicked(&m_SaveButton, sf::Mouse::Left, &m_Data->window))
			{
				std::cout << "Switch to the Save Screen from PauseState" << std::endl;
				// ..
			}

			if (m_Data->input.IsSpriteClicked(&m_ExitButton, sf::Mouse::Left, &m_Data->window))
			{
				std::cout << "Switch to the Menu Screen from PauseState" << std::endl;
				m_Data->machine.RemoveState();
				m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
			}
		}
	}

	void PauseState::Update(float deltaTime)
	{
		// empty
	}

	void PauseState::Draw(float deltaTime)
	{
		m_Data->window.clear();

		m_Data->window.draw(m_ResumeButton);
		m_Data->window.draw(m_ResumeButtonText);

		m_Data->window.draw(m_SaveButton);
		m_Data->window.draw(m_SaveButtonText);

		m_Data->window.draw(m_ExitButton);
		m_Data->window.draw(m_ExitButtonText);

		m_Data->window.display();
	}
}