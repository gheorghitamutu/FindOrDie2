#include "Player.hpp"
#include "Game.hpp"

Player::Player(ge::AssetManager *assets, ge::InputManager* input) noexcept
{
	m_Body.setOrigin(m_TextureSize / 2, m_TextureSize / 2);
	m_Body.setScale({ 1.0f, 1.0f });
	m_Body.setPosition({ 0.0f, 0.0f });

	m_pView = new sf::View();
	m_pView->setSize({ (float)ge::Game::windowHeight, (float)ge::Game::windowWidth });
	m_pView->zoom(1.0f);
	m_pView->setCenter({ 0,0 });

	m_Assets = assets;
	auto textureRequired = m_Assets->GetTexture("Player_Man");
	
	for (int i = 0; i < int(AnimationIndex::Count); i++)
	{
		m_Animations.emplace_back(
			Animation(
				(int)m_TextureSize, 
				(int)(i*m_TextureSize), 
				(int)m_TextureSize, 
				(int)m_TextureSize, 
				textureRequired,
				m_NumberOfFrames,
				m_HoldTime));
	}

	m_Input = input;
}

Player::~Player()
{
	delete m_pView;
	m_pView = nullptr;
}

void Player::Update(float elapsedSec)
{
	auto pos = m_Body.getPosition();

	SetAnimationFrame();

	// auto thumbstickState = InputManager::GetInstance()->GetThumbStickLeft;  // controller
	// pos += thumbstickState * speed * elapsedSec;							   // controller

	pos += m_Direction * m_DefaultSpeed * elapsedSec;

	m_Animations[int(m_CurrentAnimation)].Update(elapsedSec);
	m_Animations[int(m_CurrentAnimation)].ApplyToSprite(&m_Body);

	m_Body.setPosition(pos);

	if (m_IsFocused)
	{
		auto playerPosition = m_Body.getPosition();
		auto viewPosition = m_pView->getCenter();

		// you try guessing that the new view position will be the player's one
		sf::Vector2f viewNewPosition = playerPosition;

		// the player has the view already centered on him
		if (m_ViewCentered.x == true && m_ViewCentered.y == true)
		{
			m_pView->setCenter(playerPosition);
		}
		else // the view is not centered on the player
		{
			auto deltaDistance = playerPosition - viewPosition;
			deltaDistance.x = abs(deltaDistance.x);
			deltaDistance.y = abs(deltaDistance.y);

			// the distance from the view center to the player can be neglected
			if (deltaDistance.x < m_ErrorRatePosition && deltaDistance.y < m_ErrorRatePosition)
			{
				m_ViewCentered = { true, true };
				viewNewPosition = { playerPosition.x, playerPosition.y };
			}
			else // the distance from the view center to the player is noticeable
			{
				if (deltaDistance.x > m_ErrorRatePosition) // x axis is too big
				{
					if ((int)viewPosition.x > (int)playerPosition.x)
						viewNewPosition.x = viewPosition.x - m_AmountToMoveView;
					else if ((int)viewPosition.x < (int)playerPosition.x)
						viewNewPosition.x = viewPosition.x + m_AmountToMoveView;
				}

				if (deltaDistance.y > m_ErrorRatePosition) // y axis is too big
				{
					if ((int)viewPosition.y > (int)playerPosition.y)
						viewNewPosition.y = viewPosition.y - m_AmountToMoveView;
					else if ((int)viewPosition.y < (int)playerPosition.y)
						viewNewPosition.y = viewPosition.y + m_AmountToMoveView;
				}

				// so the view is not yet centered on the player
				m_ViewCentered = { false, false };
			}

			// correct the view center bringing it close to the player
			m_pView->setCenter(viewNewPosition);
		}
	}
}

void Player::Draw(sf::RenderWindow* pWindow)
{
	auto viewCenter = m_pView->getCenter();
	auto viewSize = m_pView->getSize();

	sf::FloatRect rectBounds;
	rectBounds.left = viewCenter.x - viewSize.x / 2.f;
	rectBounds.top = viewCenter.y - viewSize.y / 2.f;
	rectBounds.width = viewSize.x;
	rectBounds.height = viewSize.y;

	if(m_Body.getGlobalBounds().intersects(rectBounds))
		pWindow->draw(m_Body);
}

sf::Vector2f Player::GetPosition() const
{
	return m_Body.getPosition();
}

void Player::ChangeFocus()
{
	m_IsFocused = !m_IsFocused;
}

sf::View * Player::GetView()
{
	return m_pView;
}

void Player::ProcessEvents(sf::Event * event)
{
	m_Direction = { 0, 0 };

	if (m_Input->IsKeyPressed(ge::InputKeys::Up))
	{
		m_Direction.y = -1;
	}
	if (m_Input->IsKeyPressed(ge::InputKeys::Down))
	{
		m_Direction.y = 1;
	}
	if (m_Input->IsKeyPressed(ge::InputKeys::Left))
	{
		m_Direction.x = -1;
	}
	if (m_Input->IsKeyPressed(ge::InputKeys::Right))
	{
		m_Direction.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		m_Direction.x *= 2;
		m_Direction.y *= 2;
	}

	if (m_Input->IsKeyPressed(ge::InputKeys::Right) && 
		m_Input->IsKeyPressed(ge::InputKeys::Left))
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}

	if (m_Input->IsKeyPressed(ge::InputKeys::Up) && 
		m_Input->IsKeyPressed(ge::InputKeys::Down))
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}

	if (m_Input->IsKeyReleased(ge::InputKeys::C, event))
	{
		m_IsFocused = !m_IsFocused;
	}
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
