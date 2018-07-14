#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "ResourceManager.h"
#include "Animation.h"

class Player
{
public:
	Player();
	~Player();
	void Update(float elapsedSec);
	void Draw(sf::RenderWindow* pWindow);
	sf::Vector2f GetPosition() const;
	void ChangeFocus();
	sf::View* GetView();
	void ProcessEvents(sf::Event* event);

private:
	sf::Sprite m_Body;
	static constexpr float m_TextureSize = 80.0f;
	sf::Vector2f m_Direction = { 0, 0 };
	static constexpr float m_DefaultSpeed = 80.0f;
	static constexpr float m_WalkingSpeed = 1.1f;
	bool m_IsFocused = false;
	sf::View* m_pView = nullptr;

public:
	enum class AnimationIndex
	{
		WalkingSouth,
		WalkingWest,
		WalkingEast,
		WalkingNorth,
		RunningSouth,
		RunningWest,
		RunningEast,
		RunningNorth,
		IdleSouth,
		IdleWest,
		IdleEast,
		IdleNorth,
		WalkingSouthWest,
		WalkingNorthWest,
		WalkingSouthEast,
		WalkingNorthEast,
		RunningSouthWest,
		RunningNorthWest,
		RunningSouthEast,
		RunningNorthEast,
		IdleSouthWest,
		IdleNorthWest,
		IdleSouthEast,
		IdleNorthEast,
		Count
	};

private:
	Animation m_Animations[(int)AnimationIndex::Count];
	AnimationIndex m_CurrentAnimation = AnimationIndex::IdleSouth;

private:
	void SetAnimationFrame();
};

