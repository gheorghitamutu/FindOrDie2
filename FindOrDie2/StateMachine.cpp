#include "stdafx.h"
#include "StateMachine.hpp"


namespace GameState
{
	void GameState::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		m_IsAdding = true;
		m_IsReplacing = isReplacing;

		m_NewState = std::move(newState);
	}

	void GameState::StateMachine::RemoveState()
	{
		m_IsRemoving = true;
	}

	void GameState::StateMachine::ProcessStateChanges()
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

	StateRef & GameState::StateMachine::GetActiveState()
	{
		return m_States.top();
	}
}