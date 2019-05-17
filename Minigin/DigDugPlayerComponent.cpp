#include "MiniginPCH.h"
#include "DigDugPlayerComponent.h"
#include "DigDugPlayerStates.h"
#include "TransformComponent.h"

DigDugPlayerComponent::DigDugPlayerComponent(std::weak_ptr<DigDugLevelComponent> pLevel)
	:m_pLevel(pLevel)
{
	m_StateMachine = std::make_shared<dae::FiniteStateMachine>(new DigDugIdleState());
	//m_StateMachine->AddEvent("Pump");
	//m_StateMachine->AddEvent("Die");
}

void DigDugPlayerComponent::Pump()
{
	/*m_StateMachine->TriggerEvent("Pump");*/
}

void DigDugPlayerComponent::Die()
{
	/*m_StateMachine->TriggerEvent("Die");*/
}

void DigDugPlayerComponent::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
	m_pTransform = GetGameObject()->GetComponent<dae::TransformComponent>();
}

void DigDugPlayerComponent::Update(float)
{
	//m_StateMachine->Update(deltaTime, GetGameObject());
	//Give Player The Right Transform depending on m_Forward
	if(abs(m_Forward.y) > 0)
	{
		m_pTransform.lock()->SetRotation(90);
		if (m_Forward.y < 0)
			m_pTransform.lock()->SetScale(glm::vec2(-1, 1));
		else
			m_pTransform.lock()->SetScale(glm::vec2(1, 1));
	}

	if (abs(m_Forward.x) > 0)
	{
		m_pTransform.lock()->SetRotation(0);
		if (m_Forward.x < 0)
			m_pTransform.lock()->SetScale(glm::vec2(-1, 1));
		else
			m_pTransform.lock()->SetScale(glm::vec2(1, 1));
	}
	m_MoveDirection = glm::vec2{ 0,0 };
}
