#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_Body.setOrigin(m_TextureSize / 2, m_TextureSize / 2);
	m_Body.setScale({ 2.4f, 2.4f });
	m_Body.setPosition({ 0.0f, 0.0f });

	auto textureRequired = ResourceManager::GetInstance()->RequestTexture("Player_Man");
	
	for (int i = 0; i < int(AnimationIndex::Count); i++)
	{
		m_Animations[i] = 
			Animation(
				(int)m_TextureSize, 
				(int)(i*m_TextureSize), 
				(int)m_TextureSize, 
				(int)m_TextureSize, 
				textureRequired);
	}
}


Player::~Player()
{
}

void Player::Update(float elapsedSec)
{
	auto input = InputManager::GetInstance();
	auto pos = m_Body.getPosition();
	m_Direction = { 0, 0 };

	if (input->IsActionTriggered(InputKeys::Up))
	{
		m_Direction.y = -1;
	}
	if (input->IsActionTriggered(InputKeys::Down))
	{
		m_Direction.y = 1;
	}
	if (input->IsActionTriggered(InputKeys::Left))
	{
		m_Direction.x = -1;
	}
	if (input->IsActionTriggered(InputKeys::Right))
	{
		m_Direction.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		m_Direction.x *= 2;
		m_Direction.y *= 2;
	}

	if (input->IsActionTriggered(InputKeys::Right) && input->IsActionTriggered(InputKeys::Left))
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}

	if (input->IsActionTriggered(InputKeys::Up) && input->IsActionTriggered(InputKeys::Down))
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}

	if (input->IsActionTriggered(InputKeys::C))
	{
		m_IsFocused = !m_IsFocused;
	}

	SetAnimationFrame();

	// auto thumbstickState = InputManager::GetInstance()->GetThumbStickLeft;  // controller
	// pos += thumbstickState * speed * elapsedSec;							   // controller

	pos += m_Direction * m_DefaultSpeed * elapsedSec;

	m_Animations[int(m_CurrentAnimation)].Update(elapsedSec);
	m_Animations[int(m_CurrentAnimation)].ApplyToSprite(&m_Body);

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

bool Player::IsFocused()
{
	return m_IsFocused;
}

void Player::SetAnimationFrame()
{
	if (m_Direction.x == 0.0f && m_Direction.y > 0.0f)
	{
		if (m_Direction.y > m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningSouth;
		else
			m_CurrentAnimation = AnimationIndex::WalkingSouth;
	}
	else if (m_Direction.x > 0.0f && m_Direction.y > 0.0f)
	{
		if (m_Direction.x > m_WalkingSpeed && m_Direction.y > m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningSouthEast;
		else
			m_CurrentAnimation = AnimationIndex::WalkingSouthEast;
	}
	else if (m_Direction.x > 0.0f && m_Direction.y == 0.0f)
	{
		if (m_Direction.x > m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningEast;
		else
			m_CurrentAnimation = AnimationIndex::WalkingEast;
	}
	else if (m_Direction.x < 0.0f && m_Direction.y > 0.0f)
	{
		if (m_Direction.x < -m_WalkingSpeed && m_Direction.y > m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningSouthWest;
		else
			m_CurrentAnimation = AnimationIndex::WalkingSouthWest;

	}
	else if (m_Direction.x < 0.0f && m_Direction.y == 0.0f)
	{
		if (m_Direction.x < -m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningWest;
		else
			m_CurrentAnimation = AnimationIndex::WalkingWest;
	}
	else if (m_Direction.x < 0.0f && m_Direction.y < 0.0f)
	{
		if (m_Direction.x < -m_WalkingSpeed && m_Direction.y < -m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningNorthWest;
		else
			m_CurrentAnimation = AnimationIndex::WalkingNorthWest;
	}
	else if (m_Direction.x == 0.0f && m_Direction.y < 0.0f)
	{
		if (m_Direction.y < -m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningNorth;
		else
			m_CurrentAnimation = AnimationIndex::WalkingNorth;
	}
	else if (m_Direction.x > 0.0f && m_Direction.y < 0.0f)
	{
		if (m_Direction.x > m_WalkingSpeed && m_Direction.y < -m_WalkingSpeed)
			m_CurrentAnimation = AnimationIndex::RunningNorthEast;
		else
			m_CurrentAnimation = AnimationIndex::WalkingNorthEast;
	}
	else
	{
		switch (m_CurrentAnimation)
		{
			case AnimationIndex::WalkingSouth:
			case AnimationIndex::RunningSouth:
				m_CurrentAnimation = AnimationIndex::IdleSouth;
				break;
			case AnimationIndex::WalkingNorth:
			case AnimationIndex::RunningNorth:
				m_CurrentAnimation = AnimationIndex::IdleNorth;
				break;
			case AnimationIndex::WalkingEast:
			case AnimationIndex::RunningEast:
				m_CurrentAnimation = AnimationIndex::IdleEast;
				break;
			case AnimationIndex::WalkingWest:
			case AnimationIndex::RunningWest:
				m_CurrentAnimation = AnimationIndex::IdleWest;
				break;
			case AnimationIndex::WalkingSouthEast:
			case AnimationIndex::RunningSouthEast:
				m_CurrentAnimation = AnimationIndex::IdleSouthEast;
				break;
			case AnimationIndex::WalkingNorthEast:
			case AnimationIndex::RunningNorthEast:
				m_CurrentAnimation = AnimationIndex::IdleNorthEast;
				break;
			case AnimationIndex::WalkingSouthWest:
			case AnimationIndex::RunningSouthWest:
				m_CurrentAnimation = AnimationIndex::IdleNorthWest;
				break;
			case AnimationIndex::WalkingNorthWest:
			case AnimationIndex::RunningNorthWest:
				m_CurrentAnimation = AnimationIndex::IdleNorthWest;
				break;
		};
	}
}
