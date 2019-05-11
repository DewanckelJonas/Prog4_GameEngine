#include "MiniginPCH.h"
#include "FiniteStateMachine.h"
#include "IState.h"


dae::FiniteStateMachine::~FiniteStateMachine()
{
	delete m_pState;
}

void dae::FiniteStateMachine::Update(float deltaTime, GameObject* gameObject)
{
	IState* pNewState = m_pState->Update(gameObject, deltaTime);
	if (pNewState != nullptr)
	{
		m_pState->Exit(gameObject);
		delete m_pState;
		m_pState = pNewState;

		// Call the enter action on the new state.
		m_pState->Enter(gameObject);
	}
}
