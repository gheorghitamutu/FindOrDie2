#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace ge
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();

		void ProcessStateChanges();

		StateRef &GetActiveState();

	private:
		std::stack<StateRef> m_States;
		StateRef m_NewState;

		bool m_IsRemoving;
		bool m_IsAdding;
		bool m_IsReplacing;
	};
}

