#include "StateMachine.hpp"
#include <iostream>

namespace ge
{
	state_machine::state_machine(state_machine* other)
	{
	}

	void state_machine::add_state(const std::shared_ptr<state>& new_state, const bool is_replacing)
	{
		new_state_ = new_state;
		is_adding_ = true;
		is_replacing_ = is_replacing;
	}

	void state_machine::remove_state()
	{
		is_removing_ = true;
	}

	void state_machine::process_state_changes()
	{
		if (is_removing_ && !m_states_.empty())
		{
			m_states_.pop();

			if (!m_states_.empty())
			{
				m_states_.top()->resume();
			}

			is_removing_ = false;

			std::wcout << L"State removed! States queue size: " << m_states_.size() << std::endl;
		}

		if (is_adding_)
		{
			if (!m_states_.empty())
			{
				if (is_replacing_)
				{
					m_states_.pop();
				}
				else
				{
					m_states_.top()->pause();
				}
			}

			m_states_.push(new_state_);
			m_states_.top()->init();
			is_adding_ = false;

			std::wcout << L"State added! States queue size: " << m_states_.size() << std::endl;
		}
	}

	std::shared_ptr<state>& state_machine::get_active_state()
	{	
		return m_states_.top();
	}
}
