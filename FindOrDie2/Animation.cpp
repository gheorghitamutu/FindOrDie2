#include "Animation.hpp"

Animation::Animation(int x, int y, int width, int height, sf::Texture *texture, int numberOfFrames, float holdTime) :
	m_NumberOfFrames(numberOfFrames),
	m_HoldTime(holdTime)
{
	m_pTexture = texture;
	for (int i = 0; i < m_NumberOfFrames; i++)
	{
		m_Frames.emplace_back(sf::IntRect { x + i * width, y, width, height });
	}
}

void Animation::ApplyToSprite(sf::Sprite* body)
{
	body->setTexture(*m_pTexture);
	body->setTextureRect(m_Frames[m_FrameIndex]);
}

void Animation::Update(float deltaTime)
{
	m_Time += deltaTime;
	while (m_Time >= m_HoldTime)
	{
		m_Time -= m_HoldTime;
		Advance();
	}
}

Animation::~Animation()
{
}

void Animation::Advance()
{
	if (++m_FrameIndex >= m_NumberOfFrames)
	{
		m_FrameIndex = 0;
	}
}
