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

	m_pPlayer = new Player();

	m_pDefaultView = new sf::View();
	m_pDefaultView->setSize({ (float)windowHeight, (float)windowWidth });
	m_pDefaultView->zoom(1.0f);
	m_pDefaultView->setCenter({ 0,0 });

	m_pCurrentView = m_pDefaultView;
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
	}

	return true;
}

void Game::Update(float deltaTime)
{
	// InputManager::GetInstance()->Update(); // use it if you implement controller input 
	
	if(m_pPlayer->IsFocused())
		m_pCurrentView->setCenter(m_pPlayer->GetPosition());
	m_pPlayer->Update(deltaTime);

	// InputManager::GetInstance()->IsButtonPressed(XINPUT_GAMEPAD_X); // check controller button
}

void Game::Draw()
{
	m_pWindow->clear();
	m_pWindow->setView(*m_pCurrentView);
	// m_pWindow->setView(m_pWindow->getDefaultView()); // reset camera view

	// draw stuff
	m_pPlayer->Draw(m_pWindow);

	m_pWindow->display();
}
