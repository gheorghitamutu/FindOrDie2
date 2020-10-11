#pragma once

#include <SFML\Graphics.hpp>

class camera
{
public:
	camera(const std::shared_ptr<sf::RenderWindow>& window);
	~camera() = default;

	bool is_camera_dragged();
	void zoom(const float delta);
	void reset();
	void flush();

	const std::shared_ptr<sf::View> get_current_view() const;

	void set_current_view_size(const sf::Vector2f size);
	void set_current_view_center(const sf::Vector2f center);
private:
	sf::Vector2i position_;
	sf::Vector2f camera_center_;

	std::shared_ptr<sf::View> p_current_view_;
	sf::Vector2f initial_current_view_size_;

	std::shared_ptr<sf::RenderWindow> window_;

	bool right_click_pressed_;
	bool initial_position_;

	const float min_zoom_factor_ = 0.25f;
	const float max_zoom_factor_ = 2.00f;
};

