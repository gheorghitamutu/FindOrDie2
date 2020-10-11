#include "Camera.hpp"


camera::camera(const std::shared_ptr<sf::RenderWindow>& window) :
	window_(window),
	p_current_view_(std::make_shared<sf::View>(sf::View())),
	right_click_pressed_(false),
	initial_position_(true),
	initial_current_view_size_({0, 0})
{
}

bool camera::is_camera_dragged()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !right_click_pressed_)
	{
		position_ = sf::Mouse::getPosition(*window_);
		right_click_pressed_ = true;
		camera_center_ = p_current_view_->getCenter();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		right_click_pressed_ = false;
	}

	if (right_click_pressed_)
	{
		const auto delta_position_ = position_ - sf::Mouse::getPosition(*window_);
		p_current_view_->setCenter(camera_center_.x + delta_position_.x, camera_center_.y + delta_position_.y);
	}

	return right_click_pressed_;
}

void camera::zoom(const float delta)
{
	auto factor = 1.0f;
	const auto current_size = p_current_view_->getSize();
	const auto current_factor = abs(current_size.x) / initial_current_view_size_.x;
	const auto resulted_factor = abs((current_size * (factor + delta)).x) / initial_current_view_size_.x;

	if (resulted_factor < min_zoom_factor_)
	{
		const auto diff = min_zoom_factor_ - current_factor;
		if (diff > 0)
		{
			factor -= diff;
		}
	}
	else if (resulted_factor > max_zoom_factor_)
	{
		const auto diff = max_zoom_factor_ - current_factor;
		if (diff > 0)
		{
			factor += diff;
		}
	}
	else
	{
		factor += delta;
	}

	p_current_view_->zoom(factor);	
}

void camera::reset()
{
	window_->clear();
	window_->setView(*p_current_view_);
}

void camera::flush()
{
	window_->display();
}

const std::shared_ptr<sf::View> camera::get_current_view() const
{
	return p_current_view_;
}

void camera::set_current_view_size(const sf::Vector2f size)
{
	p_current_view_->setSize(size);
	initial_current_view_size_ = p_current_view_->getSize();
}

void camera::set_current_view_center(const sf::Vector2f center)
{
	p_current_view_->setCenter(center);
}
