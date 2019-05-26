#include "pch.h"
#include "DigDugEnemyComponent.h"
#include "DigDugPlayerStates.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"

DigDugEnemyComponent::DigDugEnemyComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel)
	:m_pLevel(wpLevel)
{
	m_StateMachine = std::make_shared<dae::FiniteStateMachine>(new PookaIdleState());
	m_StateMachine->AddEvent("Die");
	m_StateMachine->AddEvent("ToggleGhost");
	m_StateMachine->AddEvent("Fire");
}


void DigDugEnemyComponent::Die()
{
	m_StateMachine->TriggerEvent("Die");
}

void DigDugEnemyComponent::ToggleGhost()
{
	m_StateMachine->TriggerEvent("ToggleGhost");
}

void DigDugEnemyComponent::Attack()
{
}

void DigDugEnemyComponent::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
	m_pTransform = GetGameObject().lock()->GetComponent<dae::TransformComponent>();
}

void DigDugEnemyComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
	m_MoveDirection = glm::vec2{ 0,0 };
	//Give Player The Right Transform depending on m_Forward
	if (m_IsGhost)
		return;
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
	//Lock inside grid
	dae::Rect boundaries = m_pLevel.lock()->GetBoundaries();
	glm::vec3 pos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	if (pos.x < boundaries.pos.x)
		pos.x = boundaries.pos.x;
	if (pos.y < boundaries.pos.y)
		pos.y = boundaries.pos.y;
	if (pos.x > boundaries.pos.x + boundaries.width)
		pos.x = boundaries.pos.x + boundaries.width;
	if (pos.y > boundaries.pos.y + boundaries.height)
		pos.y = boundaries.pos.y + boundaries.height;
	GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->SetPosition(pos);
}
