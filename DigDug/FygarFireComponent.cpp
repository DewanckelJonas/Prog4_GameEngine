#include "pch.h"
#include "FygarFireComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "DigDugPlayerComponent.h"
#include "DigDugLevelComponent.h"

FygarFireComponent::FygarFireComponent(float speed, float lifeTime, glm::vec2 direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel)
	:m_Speed(speed)
	,m_LifeTime(lifeTime)
	,m_Direction(direction)
	,m_wpLevel(wpLevel)
{
}

FygarFireComponent::~FygarFireComponent()
{
}

void FygarFireComponent::Initialize()
{
	m_pCollider = GetGameObject().lock()->GetComponent<dae::ColliderComponent>();
	m_pTexture = GetGameObject().lock()->GetComponent<dae::TextureComponent>();
	m_pTexture.lock()->SetTargetHeight(0.01f);
	m_pTexture.lock()->SetTargetWidth(0.01f);
}

void FygarFireComponent::Update(float deltaTime)
{
	m_ElapsedSec += deltaTime;

	if (m_LifeTime < m_ElapsedSec)
	{
		GetGameObject().lock()->Destroy();
		return;
	}

	for (auto collider : m_pCollider.lock()->GetCollisions())
	{
		if (collider.otherCollider->GetTag() == "Player")
		{
			collider.otherCollider->GetGameObject().lock()->GetComponent<DigDugPlayerComponent>().lock()->Die();
		}
	}

	if (m_wpLevel.lock()->GetTile(m_pCollider.lock()->GetWorldPosition()).lock()->IsSolid())
	{
		GetGameObject().lock()->Destroy();
		return;
	}
	auto localColliderPos = m_pCollider.lock()->GetLocalPosition();
	float length = sqrt(localColliderPos.x*localColliderPos.x + localColliderPos.y*localColliderPos.y);
	m_pTexture.lock()->SetTargetWidth(length);
	m_pTexture.lock()->SetTargetHeight(m_wpLevel.lock()->GetTileHeight());
	m_pCollider.lock()->SetLocalPosition(localColliderPos + m_Direction * m_Speed * deltaTime);
}
