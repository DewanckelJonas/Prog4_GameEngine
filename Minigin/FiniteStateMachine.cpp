#include "MiniginPCH.h"
#include "FiniteStateMachine.h"
#include "IState.h"


dae::FiniteStateMachine::FiniteStateMachine(IState * startingState) :m_pState(startingState) 
{
	m_pState->SetStateMachine(this);
};


dae::FiniteStateMachine::~FiniteStateMachine()
{
	delete m_pState;
}

void dae::FiniteStateMachine::Initialize(const std::weak_ptr<GameObject>& wpGameObject)
{
	m_pState->Enter(wpGameObject);
}

void dae::FiniteStateMachine::Update(float deltaTime, const std::weak_ptr<GameObject>& wpGameObject)
{
	IState* pNewState = m_pState->Update(wpGameObject, deltaTime);
	if (pNewState != nullptr)
	{
		pNewState->SetStateMachine(this);
		m_pState->Exit(wpGameObject);
		delete m_pState;
		m_pState = pNewState;

		// Call the enter action on the new state.
		m_pState->Enter(wpGameObject);
	}
	for (auto it = m_Events.begin(); it != m_Events.end(); ++it)
	{
		it->second = false;
	}
}

void dae::FiniteStateMachine::AddEvent(const std::string & eventName)
{
	m_Events[eventName] = false;
}

bool dae::FiniteStateMachine::IsEventTriggered(const std::string & eventName) const
{
	return m_Events.at(eventName);
}

void dae::FiniteStateMachine::TriggerEvent(const std::string & eventName)
{
	m_Events.at(eventName) = true;
}
