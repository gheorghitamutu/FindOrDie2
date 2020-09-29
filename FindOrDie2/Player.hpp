#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Game.hpp"

class player
{
public:
	player(std::shared_ptr<ge::game_data>& data) noexcept;

	player(const player& other) = default;
	player(player&& other) noexcept = default;
	player& operator=(const player& other) = default;
	player& operator=(player&& other) noexcept = default;

	~player() = default;

	void update(float elapsed_sec);
	void draw(const std::unique_ptr<sf::RenderWindow>& p_window) const;
	sf::Vector2f get_position() const;
	void change_focus();
	std::shared_ptr<sf::View> get_view() const;
	void process_events(const std::shared_ptr<sf::Event>& event);

private:
	sf::Sprite body_;
	static constexpr float texture_size = 80.0f;
	sf::Vector2f direction_ = { 0, 0 };
	static constexpr float default_speed = 80.0f;
	static constexpr float walking_speed = 1.1f;
	bool is_focused_ = false;
	sf::Vector2<bool> view_centered_ = { false, false };
	std::shared_ptr<sf::View> p_view_;
	float amount_to_move_view_ = 3.f;
	int error_rate_position_ = 2;

public:
	enum class animation_index
	{
		walking_south,
		walking_west,
		walking_east,
		walking_north,
		running_south,
		running_west,
		running_east,
		running_north,
		idle_south,
		idle_west,
		idle_east,
		idle_north,
		walking_south_west,
		walking_north_west,
		walking_south_east,
		walking_north_east,
		running_south_west,
		running_north_west,
		running_south_east,
		running_north_east,
		idle_south_west,
		idle_north_west,
		idle_south_east,
		idle_north_east,
		count
	};

private:
	void set_animation_frame();

	std::vector<animation> animations_;
	animation_index current_animation_ = animation_index::idle_south;
	int number_of_frames_ = 7;
	float hold_time_ = 0.1f;

	std::shared_ptr<ge::game_data> data_;
};

