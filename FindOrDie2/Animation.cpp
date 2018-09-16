#include "Animation.hpp"

animation::animation() :
	number_of_frames_(0),
	frame_index_(0),
	hold_time_(0.0f),
	time_(0.0f),
	p_texture_(nullptr)
{
}

animation::animation(const int x, const int y, 
	const int width, const int height, 
	std::shared_ptr<sf::Texture> texture, 
	const int number_of_frames, const float hold_time) :
		number_of_frames_(number_of_frames),
		frame_index_(0),
		hold_time_(hold_time),
		time_(0),
		p_texture_(std::move(texture))
{
	for (auto i = 0; i < number_of_frames_; i++)
	{
		frames_.emplace_back(sf::IntRect{ x + i * width, y, width, height });
	}
}

void animation::apply_to_sprite(sf::Sprite* body)
{
	body->setTexture(*p_texture_);
	body->setTextureRect(frames_[frame_index_]);
}

void animation::update(const float delta_time)
{
	time_ += delta_time;
	while (time_ >= hold_time_)
	{
		time_ -= hold_time_;
		advance();
	}
}

void animation::advance()
{
	if (++frame_index_ >= number_of_frames_)
	{
		frame_index_ = 0;
	}
}
