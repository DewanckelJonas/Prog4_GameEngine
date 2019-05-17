#include "MiniginPCH.h"
#include "PookaComponent.h"
#include "DigDugPlayerStates.h"
#include "TransformComponent.h"

PookaComponent::PookaComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel)
	:m_pLevel(wpLevel)
{
	m_StateMachine = std::make_shared<dae::FiniteStateMachine>(new PookaIdleState());
	m_StateMachine->AddEvent("Die");
}


void PookaComponent::Die()
{
	m_StateMachine->TriggerEvent("Die");
}

void PookaComponent::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
	m_pTransform = GetGameObject()->GetComponent<dae::TransformComponent>();
}

void PookaComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
	//Give Player The Right Transform depending on m_Forward
	if (abs(m_Forward.y) > 0)
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
