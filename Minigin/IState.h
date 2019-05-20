#pragma once
#include "FiniteStateMachine.h"
namespace dae
{
	class GameObject;
	class IState
	{
	public:
		IState() : m_pStateMachine() {};
		virtual void Enter(const std::weak_ptr<GameObject>& wpGameobject) = 0;
		virtual void Exit(const std::weak_ptr<GameObject>& wpGameObject) = 0;
		virtual ~IState() = default;
		virtual IState* Update(const std::weak_ptr<GameObject>&, float deltaTime) = 0;
		bool IsEventTriggered(const std::string& eventName) { return m_pStateMachine->IsEventTriggered(eventName); };
		FiniteStateMachine* GetStateMachine() { return m_pStateMachine; };
		void SetStateMachine(FiniteStateMachine* pStateMachine) { m_pStateMachine = pStateMachine; }
	private:
		FiniteStateMachine* m_pStateMachine;
	};
}

