#include "MiniginPCH.h"
#include "DigDugPlayerStates.h"
#include "DigDugPlayerComponent.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"
#include "DigDugPrefabs.h"
#include "PumpComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PookaComponent.h"
#include"SpriteComponent.h"
#include "ColliderComponent.h"
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
	if (m_pPlayerComponent.lock()->GetDirection() == glm::vec2{0,0})
		return new DigDugIdleState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	
	std::cout << m_pPlayerComponent.lock()->GetForward().x << m_pPlayerComponent.lock()->GetForward().y << std::endl;

	auto dir = m_pPlayerComponent.lock()->GetDirection();
	auto pos = m_pTransformComponent.lock()->GetPosition();
	auto tileCenter = m_pPlayerComponent.lock()->GetLevel().lock()->GetNearestTileCenter(pos);

	m_pPlayerComponent.lock()->GetLevel().lock()->SetTile(pos, DigDugLevelComponent::TileType::Air);

	if (m_PrevDirection.y == 0.f && abs(dir.y) > 0.f)
	{
		if(abs(tileCenter.x - pos.x) < m_GridSnap)
		{
			m_pTransformComponent.lock()->SetPosition(glm::vec3(tileCenter.x, pos.y, 0.f));
			m_PrevDirection.y = dir.y;
			m_pPlayerComponent.lock()->SetForward(dir);
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
			m_pTransformComponent.lock()->SetPosition(glm::vec3(pos.x, tileCenter.y, 0.f));
			m_PrevDirection.x = dir.x;
			m_pPlayerComponent.lock()->SetForward(dir);
		}
	}
	else
	{
		m_PrevDirection.x = dir.x;
	}
	auto movementVec = m_pPlayerComponent.lock()->GetForward()*m_MovementSpeed*deltaTime;
	m_pTransformComponent.lock()->Translate(glm::vec3(movementVec.x, movementVec.y, 0));
	return nullptr;
}

void DigDugIdleState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
}

dae::IState * DigDugIdleState::Update(dae::GameObject *, float)
{
	if (m_pPlayerComponent.lock()->GetDirection() != glm::vec2{0,0})
		return new DigDugMoveState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	return nullptr;
}

void DigDugPumpState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
	auto transform = gameObject->GetComponent<dae::TransformComponent>();
	auto pos = transform.lock()->GetPosition();
	auto forward = m_pPlayerComponent.lock()->GetForward();
	auto pLevel = m_pPlayerComponent.lock()->GetLevel();
	auto pumpObject = DigDugPrefabs::CreatePump({ pos.x, pos.y }, forward, pLevel);
	m_pPump = pumpObject->GetComponent<PumpComponent>();
	dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(pumpObject);
}

dae::IState * DigDugPumpState::Update(dae::GameObject *, float deltaTime)
{
	if (m_pPump.expired())
	{
		return new DigDugIdleState();
	}

	m_ElapsedSec += deltaTime;
	if (m_CancelTime < m_ElapsedSec)
		m_CanCancel = true;

	if(m_CanCancel == true)
	{
		if (m_pPlayerComponent.lock()->GetDirection() != glm::vec2{ 0,0 })
		{
			if (!m_pPump.expired())
			{
				m_pPump.lock()->GetGameObject()->Destroy();
			}
			return new DigDugMoveState();
		}
	}

	if (m_TimeBetweenPumps < m_ElapsedSec) 
	{
		if (IsEventTriggered("Pump"))
		{
			m_ElapsedSec = 0;
			m_pPump.lock()->Pump();
		}
	}

	return nullptr;
}

void PookaMoveState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<PookaComponent>();
	m_pTransformComponent = gameObject->GetComponent<dae::TransformComponent>();
}

dae::IState * PookaMoveState::Update(dae::GameObject *, float deltaTime)
{
	if (m_pPlayerComponent.lock()->GetDirection() == glm::vec2{ 0,0 })
		return new PookaIdleState();
	if (IsEventTriggered("Die"))
		return new PookaDyingState();

	auto dir = m_pPlayerComponent.lock()->GetDirection();
	auto pos = m_pTransformComponent.lock()->GetPosition();
	auto tileCenter = m_pPlayerComponent.lock()->GetLevel().lock()->GetNearestTileCenter(pos);

	if (m_PrevDirection.y == 0.f && abs(dir.y) > 0.f)
	{
		if (abs(tileCenter.x - pos.x) < m_GridSnap)
		{
			m_pTransformComponent.lock()->SetPosition(glm::vec3(tileCenter.x, pos.y, 0.f));
			m_PrevDirection.y = dir.y;
			m_pPlayerComponent.lock()->SetForward(dir);
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
			m_pTransformComponent.lock()->SetPosition(glm::vec3(pos.x, tileCenter.y, 0.f));
			m_PrevDirection.x = dir.x;
			m_pPlayerComponent.lock()->SetForward(dir);
		}
	}
	else
	{
		m_PrevDirection.x = dir.x;
	}
	glm::vec2 targetTilePos = glm::vec2{ pos.x, pos.y } + m_pPlayerComponent.lock()->GetForward() * m_pPlayerComponent.lock()->GetLevel().lock()->GetTileWidth()/2.f;
	if (m_pPlayerComponent.lock()->GetLevel().lock()->GetTile(targetTilePos).lock()->IsSolid())
		return nullptr;
	auto movementVec = m_pPlayerComponent.lock()->GetForward()*m_MovementSpeed*deltaTime;
	m_pTransformComponent.lock()->Translate(glm::vec3(movementVec.x, movementVec.y, 0));
	return nullptr;
}

void PookaIdleState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<PookaComponent>();
}

dae::IState * PookaIdleState::Update(dae::GameObject *, float)
{
	if (m_pPlayerComponent.lock()->GetDirection() != glm::vec2{ 0,0 })
		return new PookaMoveState();
	if (IsEventTriggered("Die"))
		return new PookaDyingState();
	return nullptr;
}

void PookaDyingState::Enter(dae::GameObject * gameObject)
{
	dae::Sprite m_BlowUpSprite{ "PookaBlowUp.png", 1, 4 };

	gameObject->GetComponent<dae::ColliderComponent>().lock()->SetTag("DyingEnemy");
	m_pSpriteComp = gameObject->GetComponent<dae::SpriteComponent>();
	m_pSpriteComp.lock()->SetSprite(m_BlowUpSprite);
	m_pSpriteComp.lock()->SetTargetWidth(30.f);
	m_pSpriteComp.lock()->SetTargetHeight(30.f);
	m_pSpriteComp.lock()->SetPlaySpeed(0.f);
	m_pSpriteComp.lock()->SetCurrentFrame(0);
}

dae::IState * PookaDyingState::Update(dae::GameObject * gameObject, float deltaTime)
{
	m_ElapsedSec += deltaTime;
	if (IsEventTriggered("Die"))
	{
		m_ElapsedSec = 0;
		--m_Health;
		if (m_Health == 0)
			gameObject->Destroy();
	}
	else if (m_ElapsedSec > m_DeflateTime) {

		m_ElapsedSec = 0;
		++m_Health;
		if(m_Health == 4)
		{
			return new PookaIdleState();
		}
	}
	m_pSpriteComp.lock()->SetCurrentFrame(m_MaxHealth - m_Health);
	return nullptr;
}
