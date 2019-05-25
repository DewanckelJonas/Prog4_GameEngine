#include "pch.h"
#include "RockComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "DigDugPlayerComponent.h"

RockComponent::~RockComponent()
{
}

void RockComponent::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
}

void RockComponent::Update(float deltaTime)
{
	m_StateMachine->Update(deltaTime, GetGameObject());
}

void RockStable::Enter(const std::weak_ptr<dae::GameObject>& wpGameobject)
{
	m_wpColliderComponent = wpGameobject.lock()->GetComponent<dae::ColliderComponent>();
	m_wpDigDugLevelComponent = wpGameobject.lock()->GetComponent<RockComponent>().lock()->GetLevel();
	m_wpTransformComponet = wpGameobject.lock()->GetComponent<dae::TransformComponent>();
	m_StartPos = m_wpTransformComponet.lock()->GetPosition();
}

dae::IState * RockStable::Update(const std::weak_ptr<dae::GameObject>&, float deltaTime)
{
	for(auto collision : m_wpColliderComponent.lock()->GetCollisions())
	{
		if(collision.otherCollider->GetTag() == "Player")
		{
			auto otherTransform = collision.otherCollider->GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock();
			auto playerComponent = collision.otherCollider->GetGameObject().lock()->GetComponent<DigDugPlayerComponent>().lock();
			glm::vec2 offset = playerComponent->GetForward();
			offset.x = -offset.x * collision.intersection.width;
			offset.y = -offset.y * collision.intersection.height;
			otherTransform->Translate(glm::vec3(offset.x, offset.y, 0));
		}
	}

	unsigned short row, col;
	m_wpDigDugLevelComponent.lock()->GetTileRowCol(m_wpTransformComponet.lock()->GetPosition(), row, col);
	if(!m_wpDigDugLevelComponent.lock()->GetTile(row+1, col).lock()->IsSolid())
	{
		m_TimeTillDrop -= deltaTime;
		//rumble
		auto rumbleDir = glm::vec3{ rand() % (m_RumbleAmount * 20) / 20.f - m_RumbleAmount, rand() % (m_RumbleAmount * 20) / 20.f - m_RumbleAmount, 0 };
		m_wpTransformComponet.lock()->SetPosition(rumbleDir + m_StartPos);
		if(m_TimeTillDrop < 0)
		{
			m_wpTransformComponet.lock()->SetPosition(m_StartPos);
			return new RockFalling();
		}
	}
	return nullptr;
}

void RockFalling::Enter(const std::weak_ptr<dae::GameObject>& wpGameobject)
{
	m_wpColliderComponent = wpGameobject.lock()->GetComponent<dae::ColliderComponent>();
	m_wpDigDugLevelComponent = wpGameobject.lock()->GetComponent<RockComponent>().lock()->GetLevel();
	m_wpTransformComponet = wpGameobject.lock()->GetComponent<dae::TransformComponent>();
}

dae::IState * RockFalling::Update(const std::weak_ptr<dae::GameObject>& gameObject, float deltaTime)
{


	for (auto collision : m_wpColliderComponent.lock()->GetCollisions())
	{
		if (collision.otherCollider->GetTag() == "Player")
		{
			collision.otherCollider->GetGameObject().lock()->GetComponent<DigDugPlayerComponent>().lock()->Die();
		}
		if (collision.otherCollider->GetTag() == "Enemy" || collision.otherCollider->GetTag() == "DyingEnemy")
		{
			collision.otherCollider->GetGameObject().lock()->GetComponent<DigDugEnemyComponent>().lock()->Die();
			++m_NrOfEnemiesHit;
		}
	}
	unsigned short row, col;
	m_wpDigDugLevelComponent.lock()->GetTileRowCol(m_wpTransformComponet.lock()->GetPosition(), row, col);
	if (m_wpDigDugLevelComponent.lock()->GetTile(row + 1, col).lock()->IsSolid())
	{
		//TODO: SEND MESSAGE TO SCORE SYSTEM THAT DOES NOT EXIST YET
		gameObject.lock()->Destroy();
	}

	m_wpTransformComponet.lock()->Translate(glm::vec3(0, m_DropSpeed*deltaTime, 0));
	return nullptr;
}
