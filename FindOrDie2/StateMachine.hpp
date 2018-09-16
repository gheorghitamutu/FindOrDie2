#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace ge
{
	class state_machine
	{
	public:
		state_machine() = default;

		state_machine(const state_machine& other) = default;
		state_machine(state_machine&& other) noexcept = default;
		explicit state_machine(state_machine* other);
		state_machine& operator=(const state_machine& other) = default;
		state_machine& operator=(state_machine&& other) noexcept = default;

		~state_machine() = default;

		void add_state(const std::shared_ptr<state>& new_state, bool is_replacing = true);
		void remove_state();

		void process_state_changes();

		std::shared_ptr<state> &get_active_state();

	private:
		std::stack<std::shared_ptr<state>> m_states_;
		std::shared_ptr<state> new_state_;

		bool is_removing_ = false;
		bool is_adding_ = false;
		bool is_replacing_ = false;
	};
}

