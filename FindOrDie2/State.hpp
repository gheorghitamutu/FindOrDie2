#pragma once

namespace ge
{
	class state
	{
	public:
		state() = default;

		state(const state& other) = default;
		state(state&& other) noexcept = default;
		state& operator=(const state& other) = default;
		state& operator=(state&& other) noexcept = default;
		
		virtual ~state() = default;

		virtual void handle_input() = 0;
		virtual void update(float delta_time) = 0;
		virtual void draw() = 0;

		virtual void init() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
	};
}
