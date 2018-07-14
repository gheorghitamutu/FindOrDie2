#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "InputManager.h"


Game::Game()
{
	m_pWindow = new sf::RenderWindow({ windowHeight, windowWidth }, m_WindowTitle);

	InputManager::GetInstance()->AddAction(InputKeys::Up, sf::Keyboard::Key::Up);
	InputManager::GetInstance()->AddAction(InputKeys::Down, sf::Keyboard::Key::Down);
	InputManager::GetInstance()->AddAction(InputKeys::Left, sf::Keyboard::Key::Left);
	InputManager::GetInstance()->AddAction(InputKeys::Right, sf::Keyboard::Key::Right);
	InputManager::GetInstance()->AddAction(InputKeys::C, sf::Keyboard::Key::C);

	m_pMap = Map::GetInstance();
	m_pMap->GenerateMap();

	m_pDefaultView = new sf::View();
	m_pDefaultView->setSize({ (float)windowHeight, (float)windowWidth });
	m_pDefaultView->zoom(1.0f);
	m_pDefaultView->setCenter({ 0,0 });

	m_pCurrentView = m_pDefaultView;

	m_pPlayer = new Player();
	m_pCurrentView = m_pPlayer->GetView();
}


Game::~Game()
{
	delete m_pWindow;
	m_pWindow = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pDefaultView;
	m_pDefaultView = nullptr;

	ResourceManager::GetInstance()->CleanUp();
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
		std::cout << "\r" << fps ;
		
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
			break;
		default:
			break;
		}
	}

	return true;
}

void Game::Update(float deltaTime)
{
	// InputManager::GetInstance()->Update(); // use it if you implement controller input 

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

	// InputManager::GetInstance()->IsButtonPressed(XINPUT_GAMEPAD_X); // check controller button
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
