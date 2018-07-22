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

		m_Data->input.AddAction(ge::InputKeys::Up,		sf::Keyboard::Key::Up);
		m_Data->input.AddAction(ge::InputKeys::Down,	sf::Keyboard::Key::Down);
		m_Data->input.AddAction(ge::InputKeys::Left,	sf::Keyboard::Key::Left);
		m_Data->input.AddAction(ge::InputKeys::Right,	sf::Keyboard::Key::Right);
		m_Data->input.AddAction(ge::InputKeys::C,		sf::Keyboard::Key::C);
		m_Data->input.AddAction(ge::InputKeys::Esc,		sf::Keyboard::Key::Escape);

		m_pMap = new Map(&m_Data->assets);

		m_pDefaultView = new sf::View();
		m_pDefaultView->setSize({ (float)windowHeight, (float)windowWidth });
		m_pDefaultView->zoom(1.0f);
		m_pDefaultView->setCenter({ 0,0 });

		m_pCurrentView = m_pDefaultView;

		m_pPlayer = new Player(&m_Data->assets, &m_Data->input);
		m_pCurrentView = m_pPlayer->GetView();

		m_pMap->SetView(m_pCurrentView);

		std::thread generateMapThread(&Map::GenerateMap, m_pMap);
		generateMapThread.detach();

		Run();
	}

	Game::~Game()
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;

		delete m_pDefaultView;
		m_pDefaultView = nullptr;

		delete m_pMap;
		m_pMap = nullptr;
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

	bool Game::ProcessEvents()
	{
		sf::Event event;
		while (m_Data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Data->window.close();
				return false;
			}

			switch (m_CurrentGameState)
			{
			case GameState::Running:
				m_pPlayer->ProcessEvents(&event);

				if (m_Data->input.IsKeyReleased(ge::InputKeys::Esc, &event))
					m_CurrentGameState = GameState::Pause;
				break;
			case GameState::Pause:
				if (m_Data->input.IsKeyReleased(ge::InputKeys::Esc, &event))
					m_CurrentGameState = GameState::Running;
				break;
			default:
				break;
			}
		}

		return true;
	}

	void Game::Update(float deltaTime)
	{
		switch (m_CurrentGameState)
		{
		case GameState::MainMenu:
			// Menu State
			// ...
			break;
		case GameState::Running:
			// Running State
			m_pPlayer->Update(deltaTime);
			break;
		default:
			break;
		}
	}

	void Game::Draw()
	{
		m_Data->window.clear();
		m_Data->window.setView(*m_pCurrentView);

		// draw stuff
		switch (m_CurrentGameState)
		{
		case GameState::MainMenu:
			// Menu State
			// ...
			break;
		case GameState::Running:
			// Running State
			m_pMap->Draw(&m_Data->window);
			m_pPlayer->Draw(&m_Data->window);
			break;
		default:
			break;
		}

		m_Data->window.display();
	}
}