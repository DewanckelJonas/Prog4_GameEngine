#include "MiniginPCH.h"
#include "PumpComponent.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "DigDugLevelComponent.h"


PumpComponent::PumpComponent(float speed, float lifeTime, glm::vec2 direction, DigDugLevelComponent* pLevel)
	:m_LifeTime(lifeTime)
	,m_Speed(speed)
	,m_pLevel(pLevel)
	,m_Direction(direction)
{
}

void PumpComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<dae::ColliderComponent>();
	m_pTexture = GetGameObject()->GetComponent<dae::TextureComponent>();
	m_pTexture->SetTargetHeight(0.01f);
	m_pTexture->SetTargetWidth(0.01f);
}

void PumpComponent::Update(float deltaTime)
{
	m_LifeTime -= deltaTime;
	if (m_LifeTime < 0)
		GetGameObject()->Destroy();
	if (m_pLevel->GetTile(m_pCollider->GetWorldPosition()).lock()->IsSolid())
		GetGameObject()->Destroy();
	auto localColliderPos = m_pCollider->GetLocalPosition();
	float length = sqrt(localColliderPos.x*localColliderPos.x + localColliderPos.y*localColliderPos.y);
	m_pTexture->SetTargetWidth(length);
	m_pTexture->SetTargetHeight(m_pLevel->GetTileHeight());
	m_pCollider->SetLocalPosition(localColliderPos + m_Direction * m_Speed * deltaTime);
	for(auto collider : m_pCollider->GetCollisions())
	{
		if(collider.otherCollider->GetTag() == "Enemy")
		{
		}
	}

}

