#pragma once
#include "SFML\Graphics.hpp"

class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, sf::Texture *texture);
	void ApplyToSprite(sf::RectangleShape* body);
	void Update(float deltaTime);
	~Animation();
private:
	void Advance();

private:
	static constexpr int m_NumberOfFrames = 7;
	static constexpr float m_HoldTime = 0.1f;
	float m_Time = 0.0f;
	sf::Texture* m_pTexture = nullptr;
	sf::IntRect m_Frames[m_NumberOfFrames];
	int m_FrameIndex = 0;
};
