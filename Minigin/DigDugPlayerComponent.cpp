#include "MiniginPCH.h"
#include "DigDugPlayerComponent.h"
#include "DigDugPlayerStates.h"

DigDugPlayerComponent::DigDugPlayerComponent(DigDugLevelComponent* pLevel)
	:m_pLevel(pLevel)
{
	m_StateMachine = new dae::FiniteStateMachine(new DigDugIdleState());
	m_StateMachine->AddEvent("Pump");
	m_StateMachine->AddEvent("Die");
}


DigDugPlayerComponent::~DigDugPlayerComponent()
{
	delete m_StateMachine;
}

void DigDugPlayerComponent::Pump()
{
	m_StateMachine->TriggerEvent("Pump");
}

void DigDugPlayerComponent::Die()
{
	m_StateMachine->TriggerEvent("Die");
}

void DigDugPlayerComponent::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
}

void DigDugPlayerComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
	m_Direction = glm::vec2{ 0,0 };
}
