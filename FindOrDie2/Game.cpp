#include "stdafx.h"
#include "Game.h"
#include "ResourceManager.h"
#include "InputManager.h"

Game::Game()
{
	m_pWindow = new sf::RenderWindow({ 800, 600 }, "Game");
	m_Rect.setSize({ 100.0f, 100.0f });
	m_Rect.setPosition({ 100.0f, 100.0f });
	m_Rect.setTexture(ResourceManager::GetInstance()->RequestTexture("Ghost"));

	InputManager::GetInstance()->AddAction(InputKeys::Up, sf::Keyboard::Key::Up);
	InputManager::GetInstance()->AddAction(InputKeys::Down, sf::Keyboard::Key::Down);
	InputManager::GetInstance()->AddAction(InputKeys::Left, sf::Keyboard::Key::Left);
	InputManager::GetInstance()->AddAction(InputKeys::Right, sf::Keyboard::Key::Right);
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
	auto input = InputManager::GetInstance();
	auto pos = m_Rect.getPosition();

	sf::Vector2<float> velocity;
	float speed = 200.0f;

	if (input->IsActionTriggered(InputKeys::Up))
	{
		velocity.y = -speed;
	}
	if (input->IsActionTriggered(InputKeys::Down))
	{
		velocity.y = speed;
	}
	if (input->IsActionTriggered(InputKeys::Left))
	{
		velocity.x = -speed;
	}
	if (input->IsActionTriggered(InputKeys::Right))
	{
		velocity.x = speed;
	}

	pos += velocity * deltaTime;

	m_Rect.setPosition(pos);
}

void Game::Draw()
{
	m_pWindow->clear();

	// draw stuff
	m_pWindow->draw(m_Rect);


	m_pWindow->display();
}
