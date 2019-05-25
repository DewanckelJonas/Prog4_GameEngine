#include "pch.h"
#include "DigDugPlayerStates.h"
#include "DigDugPlayerComponent.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"
#include "DigDugPrefabs.h"
#include "PumpComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DigDugEnemyComponent.h"
#include"SpriteComponent.h"
#include "ColliderComponent.h"
#include "FygarFireComponent.h"
#include <SubjectComponent.h>

void DigDugMoveState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pPlayerComponent = gameObject.lock()->GetComponent<DigDugPlayerComponent>();
	m_pTransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
}

void DigDugMoveState::Exit(const std::weak_ptr<dae::GameObject>&)
{
}

dae::IState * DigDugMoveState::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
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

void DigDugIdleState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pPlayerComponent = gameObject.lock()->GetComponent<DigDugPlayerComponent>();
}

dae::IState * DigDugIdleState::Update(const std::weak_ptr<dae::GameObject>&, float)
{
	if (m_pPlayerComponent.lock()->GetDirection() != glm::vec2{0,0})
		return new DigDugMoveState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	return nullptr;
}

void DigDugPumpState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pPlayerComponent = gameObject.lock()->GetComponent<DigDugPlayerComponent>();
	auto transform = gameObject.lock()->GetComponent<dae::TransformComponent>();
	auto pos = transform.lock()->GetPosition();
	auto forward = m_pPlayerComponent.lock()->GetForward();
	auto pLevel = m_pPlayerComponent.lock()->GetLevel();
	auto pumpObject = DigDugPrefabs::CreatePump({ pos.x, pos.y }, forward, pLevel);
	m_pPump = pumpObject->GetComponent<PumpComponent>();
	dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(pumpObject);
}

dae::IState * DigDugPumpState::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
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
				m_pPump.lock()->GetGameObject().lock()->Destroy();
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

void PookaMoveState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pPlayerComponent = gameObject.lock()->GetComponent<DigDugEnemyComponent>();
	m_pTransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
}

dae::IState * PookaMoveState::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
{
	if (m_pPlayerComponent.lock()->GetDirection() == glm::vec2{ 0,0 })
		return new PookaIdleState();
	if (IsEventTriggered("Die"))
		return new PookaDyingState();
	if (m_GhostCoolDown > 0)
		m_GhostCoolDown -= deltaTime;
	else if (IsEventTriggered("ToggleGhost"))
	{
		return new PookaGhostState();
	}
	if(IsEventTriggered("Fire"))
	{
		return new EnemyFireState();
	}

	auto dir = m_pPlayerComponent.lock()->GetDirection();
	auto pos = m_pTransformComponent.lock()->GetPosition();
	auto tileCenter = m_pPlayerComponent.lock()->GetLevel().lock()->GetNearestTileCenter(pos);

	if (abs(m_PrevDirection.x) > 0 && abs(dir.x))
	{
		m_PrevDirection.x = dir.x;
		m_pPlayerComponent.lock()->SetForward(dir);
	}

	if (abs(m_PrevDirection.y) > 0 && abs(dir.y))
	{
		m_PrevDirection.y = dir.y;
		m_pPlayerComponent.lock()->SetForward(dir);
	}

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

void PookaIdleState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pPlayerComponent = gameObject.lock()->GetComponent<DigDugEnemyComponent>();
}

dae::IState * PookaIdleState::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
{
	if (m_pPlayerComponent.lock()->GetDirection() != glm::vec2{ 0,0 })
		return new PookaMoveState();
	if (IsEventTriggered("Die"))
		return new PookaDyingState();
	if (m_GhostCoolDown > 0)
		m_GhostCoolDown -= deltaTime;
	else if (IsEventTriggered("ToggleGhost"))
	{
		return new PookaGhostState();
	}
	if (IsEventTriggered("Fire"))
	{
		return new EnemyFireState();
	}
	return nullptr;
}

void PookaDyingState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pSpriteComp = gameObject.lock()->GetComponent<dae::SpriteComponent>();
	gameObject.lock()->GetComponent<dae::ColliderComponent>().lock()->SetTag("DyingEnemy");
	auto sprite = gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetBlowUpSprite();
	m_pSpriteComp.lock()->SetSprite(sprite);
	m_pSpriteComp.lock()->SetTargetWidth(30.f);
	m_pSpriteComp.lock()->SetTargetHeight(30.f);
	m_pSpriteComp.lock()->SetPlaySpeed(0.f);
	m_pSpriteComp.lock()->SetCurrentFrame(0);
}

void PookaDyingState::Exit(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pSpriteComp.lock()->SetSprite(gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetWalkSprite());
	m_pSpriteComp.lock()->SetTargetWidth(20.f);
	m_pSpriteComp.lock()->SetTargetHeight(20.f);
	m_pSpriteComp.lock()->SetPlaySpeed(1.f);
	gameObject.lock()->GetComponent<dae::ColliderComponent>().lock()->SetTag("Enemy");
}

dae::IState * PookaDyingState::Update(const std::weak_ptr<dae::GameObject>& gameObject, float deltaTime)
{
	m_ElapsedSec += deltaTime;
	if (IsEventTriggered("Die"))
	{
		m_ElapsedSec = 0;
		--m_Health;
		if (m_Health == 0)
			gameObject.lock()->Destroy();
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

void PookaGhostState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pSpriteComp = gameObject.lock()->GetComponent<dae::SpriteComponent>();
	m_pSpriteComp.lock()->SetSprite(gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetGhostSprite());
	m_wpPookaComponent = gameObject.lock()->GetComponent<DigDugEnemyComponent>();
	m_wpTransformComponent = gameObject.lock()->GetComponent<dae::TransformComponent>();
	m_wpPookaComponent.lock()->SetGhost(true);
}

dae::IState * PookaGhostState::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
{
	if (IsEventTriggered("Die"))
		return new PookaDyingState();

	auto spTransform = m_wpTransformComponent.lock();
	auto spPooka = m_wpPookaComponent.lock();

	if (m_MinGhostDuration > 0)
		m_MinGhostDuration -= deltaTime;
	else if (IsEventTriggered("ToggleGhost"))
	{
		auto pos = spTransform->GetPosition();
		if (spPooka->GetLevel().lock()->GetTile(pos).lock()->IsSolid())
			return nullptr;
		auto tileCenter = spPooka->GetLevel().lock()->GetNearestTileCenter(pos);
		if (abs(tileCenter.y - pos.y) < m_GridSnap)
		{
			spTransform->SetPosition(glm::vec3(pos.x, tileCenter.y, 0.f));
			return new PookaIdleState();
		}
		if (abs(tileCenter.x - pos.x) < m_GridSnap)
		{
			spTransform->SetPosition(glm::vec3(tileCenter.x, pos.y, 0.f));
			return new PookaIdleState();
		}

	}
	auto dir = spPooka->GetDirection();
	spPooka->SetForward(dir);
	glm::vec3 movementVector = glm::vec3(dir.x, dir.y, 0) * m_Speed * deltaTime;
	spTransform->Translate(movementVector);
	return nullptr;
}

void PookaGhostState::Exit(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_pSpriteComp = gameObject.lock()->GetComponent<dae::SpriteComponent>();
	m_pSpriteComp.lock()->SetSprite(gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetWalkSprite());
	m_wpPookaComponent.lock()->SetGhost(false);
}

void EnemyFireState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_wpEnemyComponent = gameObject.lock()->GetComponent<DigDugEnemyComponent>();
	m_wpSpriteComponent = gameObject.lock()->GetComponent<dae::SpriteComponent>();
	m_wpSpriteComponent.lock()->SetSprite(gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetChargeSprite());
	
}

dae::IState * EnemyFireState::Update(const std::weak_ptr<dae::GameObject>& gameObject, float deltaTime)
{
	if (IsEventTriggered("Die"))
	{
		if (!m_wpFire.expired())
			m_wpFire.lock()->GetGameObject().lock()->Destroy();
		return new PookaDyingState();
	}

	m_ChargeDuration -= deltaTime;
	if (m_ChargeDuration < 0)
	{
		if(!m_IsFiring)
		{
			auto transform = gameObject.lock()->GetComponent<dae::TransformComponent>();
			auto pos = transform.lock()->GetPosition();
			auto forward = m_wpEnemyComponent.lock()->GetForward();
			auto pLevel = m_wpEnemyComponent.lock()->GetLevel();
			auto fireObject = DigDugPrefabs::CreateFire({ pos.x, pos.y }, forward, pLevel);
			m_wpFire = fireObject->GetComponent<FygarFireComponent>();
			dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(fireObject);
			m_IsFiring = true;
		}
		if(m_wpFire.expired())
		{
			return new PookaIdleState();
		}
	}
	return nullptr;
}

void EnemyFireState::Exit(const std::weak_ptr<dae::GameObject>& gameObject)
{
	m_wpSpriteComponent.lock()->SetSprite(gameObject.lock()->GetComponent<DigDugEnemyComponent>().lock()->GetWalkSprite());
}

void DigDugDyingState::Enter(const std::weak_ptr<dae::GameObject>& gameObject)
{
	gameObject.lock()->GetComponent<dae::SubjectComponent>().lock()->Notify("Died", gameObject);
}
