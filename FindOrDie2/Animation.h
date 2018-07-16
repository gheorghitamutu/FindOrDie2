#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, sf::Texture *texture, int numberOfFrames, float holdTime);
	void ApplyToSprite(sf::Sprite* body);
	void Update(float deltaTime);
	~Animation();
private:
	void Advance();

private:
	int m_NumberOfFrames = 0;
	float m_HoldTime = 0;
	float m_Time = 0.0f;
	sf::Texture* m_pTexture = nullptr;
	std::vector<sf::IntRect> m_Frames;
	int m_FrameIndex = 0;
};
