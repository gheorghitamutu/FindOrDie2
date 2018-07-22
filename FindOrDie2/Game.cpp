#include "Game.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

Game::Game() noexcept
{
	m_pWindow = new sf::RenderWindow({ windowHeight, windowWidth }, m_WindowTitle);
	m_pWindow->setFramerateLimit(m_MaxFPS);

	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::Up, sf::Keyboard::Key::Up);
	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::Down, sf::Keyboard::Key::Down);
	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::Left, sf::Keyboard::Key::Left);
	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::Right, sf::Keyboard::Key::Right);
	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::C, sf::Keyboard::Key::C);
	ge::InputManager::GetInstance()->AddAction(ge::InputKeys::Esc, sf::Keyboard::Key::Escape);

	m_pMap = Map::GetInstance();

	m_pDefaultView = new sf::View();
	m_pDefaultView->setSize({ (float)windowHeight, (float)windowWidth });
	m_pDefaultView->zoom(1.0f);
	m_pDefaultView->setCenter({ 0,0 });

	m_pCurrentView = m_pDefaultView;

	m_pPlayer = new Player();
	m_pCurrentView = m_pPlayer->GetView();

	m_pMap->SetView(m_pCurrentView);
	
	std::thread generateMapThread(&Map::GenerateMap, m_pMap);
	generateMapThread.detach();
}

Game::~Game()
{
	delete m_pWindow;
	m_pWindow = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pDefaultView;
	m_pDefaultView = nullptr;

	ge::AssetManager::GetInstance()->CleanUp();
	Map::GetInstance()->CleanUp();
}

void Game::Run()
{
	sf::Clock clock;
	float deltaTime{};

	bool isRunning = true;
	while (isRunning)
	{
		// calculate time between events
		deltaTime = clock.restart().asSeconds();

		// check fps
		float fps = 1.0f / deltaTime;
		//std::cout << "\r" << fps ;

		// check events
		isRunning = ProcessEvents();
		if (!isRunning) return;

		// update
		Update(deltaTime);

		// draw/render
		Draw();
	}
}

bool Game::ProcessEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_pWindow->close();
			return false;
		}

		switch (m_CurrentGameState)
		{
		case GameState::Running:
			m_pPlayer->ProcessEvents(&event);

			if (ge::InputManager::GetInstance()->IsKeyReleased(ge::InputKeys::Esc, &event))
				m_CurrentGameState = GameState::Pause;
			break;
		case GameState::Pause:
			if (ge::InputManager::GetInstance()->IsKeyReleased(ge::InputKeys::Esc, &event))
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
	m_pWindow->clear();
	m_pWindow->setView(*m_pCurrentView);

	// draw stuff
	switch (m_CurrentGameState)
	{
	case GameState::MainMenu:
		// Menu State
		// ...
		break;
	case GameState::Running:
		// Running State
		m_pMap->Draw(m_pWindow);
		m_pPlayer->Draw(m_pWindow);
		break;
	default:
		break;
	}

	m_pWindow->display();
}
