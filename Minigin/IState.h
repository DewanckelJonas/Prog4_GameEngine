#pragma once
#include "FiniteStateMachine.h"
namespace dae
{
	class GameObject;
	class IState
	{
	public:
		IState() : m_pStateMachine() {};
		virtual void Enter(GameObject*) = 0;
		virtual void Exit(GameObject*) = 0;
		virtual IState* Update(GameObject*, float deltaTime) = 0;
		bool IsEventTriggered(const std::string& eventName) { return m_pStateMachine->IsEventTriggered(eventName); };
		FiniteStateMachine* GetStateMachine() { return m_pStateMachine; };
		void SetStateMachine(FiniteStateMachine* pStateMachine) { m_pStateMachine = pStateMachine; }
	private:
		FiniteStateMachine* m_pStateMachine;
	};
}

