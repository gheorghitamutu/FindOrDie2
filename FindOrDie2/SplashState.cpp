#include <sstream>
#include <iostream>

#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.h"

namespace ge
{
	SplashState::SplashState(GameDataRef data) :
		m_Data(data)
	{
	}


	SplashState::~SplashState()
	{
	}

	void SplashState::Init()
	{
		m_Data->assets.LoadTexture(
			"Splash State Background", 
			SPLASH_BACKGROUND);

		auto texture = m_Data->assets.GetTexture("Splash State Background");
		m_Background.setTexture(*texture);

		// resize the background to fit any resolution
		auto textureSize = texture->getSize();
		auto scaleFactor = sf::Vector2f((float)SCREEN_WIDTH / textureSize.x, (float)SCREEN_HEIGHT / textureSize.y);
		auto currentScaleFactor = m_Background.getScale();
		auto newScaleFactor = sf::Vector2f(currentScaleFactor.x * scaleFactor.x, currentScaleFactor.y * scaleFactor.y);
		m_Background.scale(newScaleFactor);
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (m_Data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_Data->window.close();
			}
		}
	}

	void SplashState::Update(float deltaTime)
	{
		if (m_Clock.getElapsedTime().asSeconds() > SPLASH_TIMEOUT)
		{
			// Switch to the Main Menu
			std::cout << "Switch to the Main Menu" << std::endl;
			m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
		}
	}

	void SplashState::Draw(float deltaTime)
	{
		m_Data->window.clear(sf::Color::Black);

		m_Data->window.draw(m_Background);

		m_Data->window.display();
	}
}