#include "MiniginPCH.h"
#include "DigDugPlayerStates.h"
#include "DigDugPlayerComponent.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"
#include "DigDugPrefabs.h"
#include "PumpComponent.h"
#include "SceneManager.h"
#include "Scene.h"

void DigDugMoveState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
	m_pTransformComponent = gameObject->GetComponent<dae::TransformComponent>();
}

void DigDugMoveState::Exit(dae::GameObject *)
{
}

dae::IState * DigDugMoveState::Update(dae::GameObject *, float deltaTime)
{
	if (m_pPlayerComponent->GetDirection() == glm::vec2{0,0})
		return new DigDugIdleState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	
	std::cout << m_pPlayerComponent->GetForward().x << m_pPlayerComponent->GetForward().y << std::endl;

	auto dir = m_pPlayerComponent->GetDirection();
	auto pos = m_pTransformComponent->GetPosition();
	auto tileCenter = m_pPlayerComponent->GetLevel()->GetNearestTileCenter(pos);

	m_pPlayerComponent->GetLevel()->SetTile(pos, DigDugLevelComponent::TileType::Air);

	if (m_PrevDirection.y == 0.f && abs(dir.y) > 0.f)
	{
		if(abs(tileCenter.x - pos.x) < m_GridSnap)
		{
			m_pTransformComponent->SetPosition(glm::vec3(tileCenter.x, pos.y, 0.f));
			m_PrevDirection.y = dir.y;
			m_pPlayerComponent->SetForward(dir);
		}
	}
	else
	{
		m_PrevDirection.y = dir.y;
	}

	if (m_PrevDirection.x == 0.f && abs(dir.x) > 0.f)
	{
		if (abs(tileCenter.y - pos.y) < m_GridSnap)
		{
			m_pTransformComponent->SetPosition(glm::vec3(pos.x, tileCenter.y, 0.f));
			m_PrevDirection.x = dir.x;
			m_pPlayerComponent->SetForward(dir);
		}
	}
	else
	{
		m_PrevDirection.x = dir.x;
	}
	auto movementVec = m_pPlayerComponent->GetForward()*m_MovementSpeed*deltaTime;
	m_pTransformComponent->Translate(glm::vec3(movementVec.x, movementVec.y, 0));
	return nullptr;
}

void DigDugIdleState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
}

dae::IState * DigDugIdleState::Update(dae::GameObject *, float)
{
	if (m_pPlayerComponent->GetDirection() != glm::vec2{0,0})
		return new DigDugMoveState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	return nullptr;
}

void DigDugPumpState::Enter(dae::GameObject * gameObject)
{
	auto transform = gameObject->GetComponent<dae::TransformComponent>();
	auto pos = transform->GetPosition();
	float rot = transform->GetRotation();
	auto scale = transform->GetScale();

	auto pLevel = gameObject->GetComponent<DigDugPlayerComponent>()->GetLevel();
	auto pumpObject = DigDugPrefabs::CreatePump({ pos.x, pos.y }, pLevel);
	pumpObject->GetComponent<dae::TransformComponent>()->SetRotation(rot);
	pumpObject->GetComponent<dae::TransformComponent>()->SetScale(scale);
	m_pPump = pumpObject->GetComponent<PumpComponent>();
	dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(pumpObject);
}
