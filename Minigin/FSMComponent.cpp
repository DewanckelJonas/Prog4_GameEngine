#include "MiniginPCH.h"
#include "FSMComponent.h"
#include "IState.h"


void dae::FSMComponent::Update(float deltaTime)
{
	IState* pNewState = m_pState->Update(GetGameObject, deltaTime);
	if (pNewState != nullptr)
	{
		m_pState->Exit(GetGameObject());
		delete m_pState;
		m_pState = pNewState;

		// Call the enter action on the new state.
		m_pState->Enter(GetGameObject());
	}
}
