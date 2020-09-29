#include "Player.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

player::player(const std::shared_ptr<ge::asset_manager>& assets, const std::shared_ptr<ge::input_manager> input) noexcept
{
	body_.setOrigin(texture_size / 2, texture_size / 2);
	body_.setScale({ 1.0f, 1.0f });
	body_.setPosition({ 0.0f, 0.0f });

	p_view_ = std::make_shared<sf::View>(sf::View());
	p_view_->setSize({ SCREEN_HEIGHT, SCREEN_WIDTH });
	p_view_->zoom(1.0f);
	p_view_->setCenter({ 0,0 });

	assets_ = assets;
	const auto texture_required = assets_->get_texture("Player_Man");
	
	for (auto i = 0; i < int(animation_index::count); i++)
	{
		animations_.emplace_back(
			animation(
				static_cast<int>(texture_size), 
				static_cast<int>(i * texture_size), 
				static_cast<int>(texture_size), 
				static_cast<int>(texture_size), 
				texture_required,
				number_of_frames_,
				hold_time_));
	}

	input_ = input;
}

void player::update(const float elapsed_sec)
{	
	auto pos = body_.getPosition();

	set_animation_frame();

	pos += direction_ * default_speed * elapsed_sec;

	animations_[int(current_animation_)].update(elapsed_sec);
	animations_[int(current_animation_)].apply_to_sprite(&body_);

	body_.setPosition(pos);

	if (is_focused_)
	{
		const auto player_position = body_.getPosition();
		const auto view_position = p_view_->getCenter();

		// you try guessing that the new view position will be the player's one
		auto view_new_position = player_position;

		// the player has the view already centered on him
		if (view_centered_.x && view_centered_.y)
		{
			p_view_->setCenter(player_position);
		}
		else // the view is not centered on the player
		{
			auto delta_distance = player_position - view_position;
			delta_distance.x = abs(delta_distance.x);
			delta_distance.y = abs(delta_distance.y);

			// the distance from the view center to the player can be neglected
			if (delta_distance.x < error_rate_position_ && delta_distance.y < error_rate_position_)
			{
				view_centered_ = { true, true };
				view_new_position = { player_position.x, player_position.y };
			}
			else // the distance from the view center to the player is noticeable
			{
				if (delta_distance.x > error_rate_position_) // x axis is too big
				{
					if (static_cast<int>(view_position.x) > static_cast<int>(player_position.x))
						view_new_position.x = view_position.x - amount_to_move_view_;
					else if (static_cast<int>(view_position.x) < static_cast<int>(player_position.x))
						view_new_position.x = view_position.x + amount_to_move_view_;
				}

				if (delta_distance.y > error_rate_position_) // y axis is too big
				{
					if (static_cast<int>(view_position.y) > static_cast<int>(player_position.y))
						view_new_position.y = view_position.y - amount_to_move_view_;
					else if (static_cast<int>(view_position.y) < static_cast<int>(player_position.y))
						view_new_position.y = view_position.y + amount_to_move_view_;
				}

				// so the view is not yet centered on the player
				view_centered_ = { false, false };
			}

			// correct the view center bringing it close to the player
			p_view_->setCenter(view_new_position);
		}
	}
}

void player::draw(const std::unique_ptr<sf::RenderWindow>& p_window) const
{
	const auto view_center = p_view_->getCenter();
	const auto view_size = p_view_->getSize();

	sf::FloatRect rect_bounds;
	rect_bounds.left = view_center.x - view_size.x / 2.f;
	rect_bounds.top = view_center.y - view_size.y / 2.f;
	rect_bounds.width = view_size.x;
	rect_bounds.height = view_size.y;

	if (body_.getGlobalBounds().intersects(rect_bounds))
	{
		p_window->draw(body_);
	}
}

sf::Vector2f player::get_position() const
{
	return body_.getPosition();
}

void player::change_focus()
{
	is_focused_ = !is_focused_;
}

std::shared_ptr<sf::View> player::get_view() const
{
	return p_view_;
}

void player::process_events(const std::shared_ptr<sf::Event>& event)
{
	direction_ = { 0, 0 };

	if (input_->is_key_pressed(ge::input_keys::up))
	{
		direction_.y = -1;
	}
	if (input_->is_key_pressed(ge::input_keys::down))
	{
		direction_.y = 1;
	}
	if (input_->is_key_pressed(ge::input_keys::left))
	{
		direction_.x = -1;
	}
	if (input_->is_key_pressed(ge::input_keys::right))
	{
		direction_.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction_.x *= 2;
		direction_.y *= 2;
	}

	if (input_->is_key_pressed(ge::input_keys::right) && 
		input_->is_key_pressed(ge::input_keys::left))
	{
		direction_.x = 0;
		direction_.y = 0;
	}

	if (input_->is_key_pressed(ge::input_keys::up) && 
		input_->is_key_pressed(ge::input_keys::down))
	{
		direction_.x = 0;
		direction_.y = 0;
	}

	if (input_->is_key_released(ge::input_keys::c, event))
	{
		is_focused_ = !is_focused_;
	}
}

void player::set_animation_frame()
{
	if (direction_.x == 0.0f && direction_.y > 0.0f)
	{
		if (direction_.y > walking_speed)
			current_animation_ = animation_index::running_south;
		else
			current_animation_ = animation_index::walking_south;
	}
	else if (direction_.x > 0.0f && direction_.y > 0.0f)
	{
		if (direction_.x > walking_speed && direction_.y > walking_speed)
			current_animation_ = animation_index::running_south_east;
		else
			current_animation_ = animation_index::walking_south_east;
	}
	else if (direction_.x > 0.0f && direction_.y == 0.0f)
	{
		if (direction_.x > walking_speed)
			current_animation_ = animation_index::running_east;
		else
			current_animation_ = animation_index::walking_east;
	}
	else if (direction_.x < 0.0f && direction_.y > 0.0f)
	{
		if (direction_.x < -walking_speed && direction_.y > walking_speed)
			current_animation_ = animation_index::running_south_west;
		else
			current_animation_ = animation_index::walking_south_west;

	}
	else if (direction_.x < 0.0f && direction_.y == 0.0f)
	{
		if (direction_.x < -walking_speed)
			current_animation_ = animation_index::running_west;
		else
			current_animation_ = animation_index::walking_west;
	}
	else if (direction_.x < 0.0f && direction_.y < 0.0f)
	{
		if (direction_.x < -walking_speed && direction_.y < -walking_speed)
			current_animation_ = animation_index::running_north_west;
		else
			current_animation_ = animation_index::walking_north_west;
	}
	else if (direction_.x == 0.0f && direction_.y < 0.0f)
	{
		if (direction_.y < -walking_speed)
			current_animation_ = animation_index::running_north;
		else
			current_animation_ = animation_index::walking_north;
	}
	else if (direction_.x > 0.0f && direction_.y < 0.0f)
	{
		if (direction_.x > walking_speed && direction_.y < -walking_speed)
			current_animation_ = animation_index::running_north_east;
		else
			current_animation_ = animation_index::walking_north_east;
	}
	else
	{
		switch (current_animation_)
		{
			case animation_index::walking_south:
			case animation_index::running_south:
				current_animation_ = animation_index::idle_south;
				break;
			case animation_index::walking_north:
			case animation_index::running_north:
				current_animation_ = animation_index::idle_north;
				break;
			case animation_index::walking_east:
			case animation_index::running_east:
				current_animation_ = animation_index::idle_east;
				break;
			case animation_index::walking_west:
			case animation_index::running_west:
				current_animation_ = animation_index::idle_west;
				break;
			case animation_index::walking_south_east:
			case animation_index::running_south_east:
				current_animation_ = animation_index::idle_south_east;
				break;
			case animation_index::walking_north_east:
			case animation_index::running_north_east:
				current_animation_ = animation_index::idle_north_east;
				break;
			case animation_index::walking_south_west:
			case animation_index::running_south_west:
				current_animation_ = animation_index::idle_north_west;
				break;
			case animation_index::walking_north_west:
			case animation_index::running_north_west:
				current_animation_ = animation_index::idle_north_west;
				break;
			default: 
				break;
		};
	}
}
