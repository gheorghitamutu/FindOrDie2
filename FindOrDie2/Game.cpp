#include "Game.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SplashState.hpp"

namespace ge
{
	Game::Game(float windowWidth, float windowHeight, std::string gameTitle) noexcept
	{
		m_Data->window.create(
			sf::VideoMode(
				(unsigned int)windowWidth, 
				(unsigned int)windowHeight),
			gameTitle,
			sf::Style::Close | sf::Style::Titlebar);
		m_Data->machine.AddState(StateRef(new SplashState(m_Data)));

		m_Data->window.setFramerateLimit(m_MaxFPS);

		Run();
	}

	Game::~Game()
	{
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = m_Clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (m_Data->window.isOpen())
		{
			m_Data->machine.ProcessStateChanges();

			// calculate time between events
			newTime = m_Clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= m_DeltaTime)
			{
				m_Data->machine.GetActiveState()->HandleInput();
				m_Data->machine.GetActiveState()->Update(m_DeltaTime);

				accumulator -= m_DeltaTime;
			}

			interpolation = accumulator / m_DeltaTime;
			m_Data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}