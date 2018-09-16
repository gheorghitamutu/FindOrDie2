#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class animation
{
public:
	animation();
	animation(int x, int y, int width, int height, std::shared_ptr<sf::Texture> texture, int number_of_frames, float hold_time);

	animation(const animation& other) = default;
	animation(animation&& other) noexcept = default;
	animation& operator=(const animation& other) = default;
	animation& operator=(animation&& other) noexcept = default;

	~animation() = default;

	void apply_to_sprite(sf::Sprite* body);
	void update(float delta_time);
private:
	void advance();

	int number_of_frames_;
	int frame_index_;

	float hold_time_;
	float time_;

	std::shared_ptr<sf::Texture> p_texture_;
	std::vector<sf::IntRect> frames_;
};
