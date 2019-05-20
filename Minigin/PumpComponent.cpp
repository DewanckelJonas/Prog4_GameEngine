#include "MiniginPCH.h"
#include "PumpComponent.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "DigDugLevelComponent.h"
#include "PookaComponent.h"


PumpComponent::PumpComponent(float speed, float lifeTime, glm::vec2 direction, const std::weak_ptr<DigDugLevelComponent>& pLevel)
	:m_LifeTime(lifeTime)
	,m_Speed(speed)
	,m_pLevel(pLevel)
	,m_Direction(direction)
{
}

void PumpComponent::Initialize()
{
	m_pCollider = GetGameObject().lock()->GetComponent<dae::ColliderComponent>();
	m_pTexture = GetGameObject().lock()->GetComponent<dae::TextureComponent>();
	m_pTexture.lock()->SetTargetHeight(0.01f);
	m_pTexture.lock()->SetTargetWidth(0.01f);
}

void PumpComponent::Update(float deltaTime)
{
	m_ElapsedSec += deltaTime;

	if (m_LifeTime < m_ElapsedSec)
	{
		GetGameObject().lock()->Destroy();
		return;
	}

	if (m_pVictim.lock())
		return;

	for (auto collider : m_pCollider.lock()->GetCollisions())
	{
		if (collider.otherCollider->GetTag() == "Enemy" || collider.otherCollider->GetTag() == "DyingEnemy")
		{
			m_pVictim = collider.otherCollider->GetGameObject();
			if (collider.otherCollider->GetTag() == "Enemy")
				Pump();
			return;
		}
	}
	
	if (m_pLevel.lock()->GetTile(m_pCollider.lock()->GetWorldPosition()).lock()->IsSolid())
	{
		GetGameObject().lock()->Destroy();
		return;
	}
	auto localColliderPos = m_pCollider.lock()->GetLocalPosition();
	float length = sqrt(localColliderPos.x*localColliderPos.x + localColliderPos.y*localColliderPos.y);
	m_pTexture.lock()->SetTargetWidth(length);
	m_pTexture.lock()->SetTargetHeight(m_pLevel.lock()->GetTileHeight());
	m_pCollider.lock()->SetLocalPosition(localColliderPos + m_Direction * m_Speed * deltaTime);

}

void PumpComponent::Pump()
{
	if(m_pVictim.lock())
	{
		m_ElapsedSec = 0;
		m_pVictim.lock()->GetComponent<PookaComponent>().lock()->Die();
		if (m_pVictim.lock()->IsDestroyed())
			GetGameObject().lock()->Destroy();
	}
}

