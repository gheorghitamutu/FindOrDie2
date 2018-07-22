#include "GameState.h"
#include "DEFINITIONS.hpp"

namespace ge
{
	GameState::GameState(GameDataRef data) :
		m_Data(data)
	{
	}


	GameState::~GameState()
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;

		delete m_pDefaultView;
		m_pDefaultView = nullptr;

		delete m_pMap;
		m_pMap = nullptr;

		
	}

	void GameState::Init()
	{
		m_pMap = new Map(&m_Data->assets);

		m_Data->input.AddAction(ge::InputKeys::Up, sf::Keyboard::Key::Up);
		m_Data->input.AddAction(ge::InputKeys::Down, sf::Keyboard::Key::Down);
		m_Data->input.AddAction(ge::InputKeys::Left, sf::Keyboard::Key::Left);
		m_Data->input.AddAction(ge::InputKeys::Right, sf::Keyboard::Key::Right);
		m_Data->input.AddAction(ge::InputKeys::C, sf::Keyboard::Key::C);
		m_Data->input.AddAction(ge::InputKeys::Esc, sf::Keyboard::Key::Escape);

		m_pDefaultView = new sf::View();
		m_pDefaultView->setSize({ (float)SCREEN_HEIGHT, (float)SCREEN_WIDTH });
		m_pDefaultView->zoom(1.0f);
		m_pDefaultView->setCenter({ 0,0 });

		m_pCurrentView = m_pDefaultView;

		m_pPlayer = new Player(&m_Data->assets, &m_Data->input);
		m_pCurrentView = m_pPlayer->GetView();

		m_pMap->SetView(m_pCurrentView);

		std::thread generateMapThread(&Map::GenerateMap, m_pMap);
		generateMapThread.detach();

		m_GameState = STATE_PLAYING;
	}

	void GameState::HandleInput()
	{
		sf::Event event;
		while (m_Data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Data->window.close();
			}

			switch (m_GameState)
			{
			case STATE_PLAYING:
				m_pPlayer->ProcessEvents(&event);

				if (m_Data->input.IsKeyReleased(ge::InputKeys::Esc, &event))
					m_GameState = STATE_PAUSE;
				break;
			case STATE_PAUSE:
				if (m_Data->input.IsKeyReleased(ge::InputKeys::Esc, &event))
					m_GameState = STATE_PLAYING;
				break;
			default:
				break;
			}
		}
	}

	void GameState::Update(float deltaTime)
	{
		switch (m_GameState)
		{
		case STATE_PLAYING:
			m_pPlayer->Update(deltaTime);
			break;
		case STATE_PAUSE:
			// ...
			break;
		default:
			break;
		}
	}

	void GameState::Draw(float deltaTime)
	{
		m_Data->window.clear();
		m_Data->window.setView(*m_pCurrentView);

		switch (m_GameState)
		{
		case STATE_PLAYING:
			m_pMap->Draw(&m_Data->window);
			m_pPlayer->Draw(&m_Data->window);
			break;
		case STATE_PAUSE:
			// ...
			break;
		default:
			break;
		}

		m_Data->window.display();
	}
}
