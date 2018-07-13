#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"

Game::Game()
{
	m_pWindow = new sf::RenderWindow({ 800, 600 }, "Game");
	m_Rect.setSize({ 100.0f, 100.0f });
	m_Rect.setPosition({ 100.0f, 100.0f });
	m_Rect.setTexture(ResourceManager::GetInstance()->RequestTexture("Ghost"));
}


Game::~Game()
{
	delete m_pWindow;
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
}

void Game::Draw()
{
	m_pWindow->clear();

	// draw stuff
	m_pWindow->draw(m_Rect);


	m_pWindow->display();
}
