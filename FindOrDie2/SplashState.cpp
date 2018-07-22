#include <sstream>
#include <iostream>

#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

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
			SPLASH_SCENE_BACKGROUND_FILEPATH);

		m_Background.setTexture(*m_Data->assets.GetTexture("Splash State Background"));
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
		if (m_Clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch to the Main Menu
			std::cout << "Switch to the Main Menu" << std::endl;
		}
	}

	void SplashState::Draw(float deltaTime)
	{
		m_Data->window.clear(sf::Color::Black);

		m_Data->window.draw(m_Background);

		m_Data->window.display();
	}
}