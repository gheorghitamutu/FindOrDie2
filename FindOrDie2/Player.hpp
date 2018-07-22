#pragma once

#include <SFML/Graphics.hpp>

#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "Animation.hpp"

class Player
{
public:
	Player(ge::AssetManager *assets, ge::InputManager* input) noexcept;
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
	sf::Vector2<bool> m_ViewCentered = { false, false };
	sf::View* m_pView = nullptr;
	float m_AmountToMoveView = 3.f;
	int m_ErrorRatePosition = 2;

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
	std::vector<Animation> m_Animations;
	AnimationIndex m_CurrentAnimation = AnimationIndex::IdleSouth;
	int m_NumberOfFrames = 7;
	float m_HoldTime = 0.1f;

private:
	void SetAnimationFrame();

private:
	ge::AssetManager* m_Assets = nullptr;
	ge::InputManager* m_Input = nullptr;
};

