#include "MiniginPCH.h"
#include "DigDugPlayerComponent.h"
#include "DigDugPlayerStates.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

DigDugPlayerComponent::DigDugPlayerComponent(std::weak_ptr<DigDugLevelComponent> pLevel)
	:m_pLevel(pLevel)
{
	m_StateMachine = std::make_shared<dae::FiniteStateMachine>(new DigDugIdleState());
	m_StateMachine->AddEvent("Pump");
	m_StateMachine->AddEvent("Die");
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
	m_pTransform = GetGameObject().lock()->GetComponent<dae::TransformComponent>();
	m_pCollider = GetGameObject().lock()->GetComponent<dae::ColliderComponent>();
}

void DigDugPlayerComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
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
	
	for(auto collision : m_pCollider.lock()->GetCollisions())
	{
		if(collision.otherCollider->GetTag() == "Enemy")
		{
			m_StateMachine->TriggerEvent("Die");
		}
	}

	m_MoveDirection = glm::vec2{ 0,0 };
}
