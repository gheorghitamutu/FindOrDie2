#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_Body.setSize({ 100.0f, 100.0f });
	m_Body.setPosition({ 0.0f, 0.0f });
	m_Body.setTexture(ResourceManager::GetInstance()->RequestTexture("Ghost"));
}


Player::~Player()
{
}

void Player::Update(float elapsedSec)
{
	auto input = InputManager::GetInstance();
	auto pos = m_Body.getPosition();

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

	// auto thumbstickState = InputManager::GetInstance()->GetThumbStickLeft;  // controller
	// pos += thumbstickState * speed * elapsedSec;							   // controller

	pos += velocity * elapsedSec;

	m_Body.setPosition(pos);
}

void Player::Draw(sf::RenderWindow* pWindow)
{
	pWindow->draw(m_Body);
}

sf::Vector2f Player::GetPosition() const
{
	return m_Body.getPosition();
}
