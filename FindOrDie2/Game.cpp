#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "InputManager.h"


Game::Game()
{
	m_pWindow = new sf::RenderWindow({ 800, 600 }, "Game");	

	InputManager::GetInstance()->AddAction(InputKeys::Up, sf::Keyboard::Key::Up);
	InputManager::GetInstance()->AddAction(InputKeys::Down, sf::Keyboard::Key::Down);
	InputManager::GetInstance()->AddAction(InputKeys::Left, sf::Keyboard::Key::Left);
	InputManager::GetInstance()->AddAction(InputKeys::Right, sf::Keyboard::Key::Right);

	m_pPlayer = new Player();

	m_View.setSize({ 800.0f, 600.0f });
	m_View.zoom(1.0f);
}


Game::~Game()
{
	delete m_pWindow;
	m_pWindow = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;
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
	
	m_View.setCenter(m_pPlayer->GetPosition());
	m_pPlayer->Update(deltaTime);

	// InputManager::GetInstance()->IsButtonPressed(XINPUT_GAMEPAD_X); // check controller button
}

void Game::Draw()
{
	m_pWindow->clear();
	m_pWindow->setView(m_View);
	// m_pWindow->setView(m_pWindow->getDefaultView()); // reset camera view

	// draw stuff
	m_pPlayer->Draw(m_pWindow);

	m_pWindow->display();
}
