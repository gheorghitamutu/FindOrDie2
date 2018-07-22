#include "StateMachine.hpp"

namespace ge
{
	void ge::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		m_IsAdding = true;
		m_IsReplacing = isReplacing;

		m_NewState = std::move(newState);
	}

	void ge::StateMachine::RemoveState()
	{
		m_IsRemoving = true;
	}

	void ge::StateMachine::ProcessStateChanges()
	{
		if (m_IsRemoving && !m_States.empty())
		{
			m_States.pop();

			if (!m_States.empty())
			{
				m_States.top()->Resume();
			}

			m_IsRemoving = false;
		}

		if (m_IsAdding)
		{
			if (!m_States.empty())
			{
				if (m_IsReplacing)
				{
					m_States.pop();
				}
				else
				{
					m_States.top()->Pause();
				}
			}

			m_States.push(std::move(m_NewState));
			m_States.top()->Init();
			m_IsAdding = false;
		}
	}

	StateRef & ge::StateMachine::GetActiveState()
	{
		return m_States.top();
	}
}