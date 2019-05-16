#include "MiniginPCH.h"
#include "DigDugPlayerComponent.h"
#include "DigDugPlayerStates.h"
#include "TransformComponent.h"

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
	m_pTransform = GetGameObject()->GetComponent<dae::TransformComponent>();
}

void DigDugPlayerComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
	//Give Player The Right Transform depending on m_Forward
	if(abs(m_Forward.y) > 0)
	{
		m_pTransform->SetRotation(90);
		if (m_Forward.y < 0)
			m_pTransform->SetScale(glm::vec2(-1, 1));
		else
			m_pTransform->SetScale(glm::vec2(1, 1));
	}

	if (abs(m_Forward.x) > 0)
	{
		m_pTransform->SetRotation(0);
		if (m_Forward.x < 0)
			m_pTransform->SetScale(glm::vec2(-1, 1));
		else
			m_pTransform->SetScale(glm::vec2(1, 1));
	}
	m_MoveDirection = glm::vec2{ 0,0 };
}
