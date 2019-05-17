#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "TransformComponent.h"

dae::ColliderComponent::ColliderComponent(const Rect & shape, const std::string& tag)
	:m_Shape{ {0,0} ,shape.width, shape.height }
	,m_Tag{tag}
	,m_LocalPos{shape.pos}
{
	CollisionSystem::GetInstance().AddCollider(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	CollisionSystem::GetInstance().RemoveCollider(this);
}

void dae::ColliderComponent::Initialize()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}

void dae::ColliderComponent::Update(float)
{
	m_Shape.pos.x = m_pTransform.lock()->GetPosition().x + m_LocalPos.x;
	m_Shape.pos.y = m_pTransform.lock()->GetPosition().y + m_LocalPos.y;
}

void dae::ColliderComponent::CheckCollision(ColliderComponent & collider)
{
	float Axmin = collider.m_Shape.pos.x;
	float Axmax = collider.m_Shape.pos.x + collider.m_Shape.width;
	float Aymax = collider.m_Shape.pos.y + collider.m_Shape.width;
	float Aymin = collider.m_Shape.pos.y;

	float Bxmin = m_Shape.pos.x;
	float Bxmax = m_Shape.pos.x + m_Shape.width;
	float Bymax = m_Shape.pos.y + m_Shape.width;
	float Bymin = m_Shape.pos.y;

	// Collision check
	if (Axmax < Bxmin || Axmin > Bxmax) return;
	if (Aymax < Bymin || Aymin > Bymax) return;

	// Get the intersection rectangle
	Collision collision;
	collision.intersection.pos.x = max(Axmin, Bxmin);
	collision.intersection.pos.y = max(Aymin, Bymin);
	collision.intersection.width = min(Axmax, Bxmax) - collision.intersection.pos.x;
	collision.intersection.height = min(Aymax, Bymax) - collision.intersection.pos.y;

	collision.otherCollider = this;
	collider.m_Collisions.push_back(collision);
	collision.otherCollider = &collider;
	m_Collisions.push_back(collision);

	return;
}

const std::vector<dae::Collision>& dae::ColliderComponent::GetCollisions()
{
	return m_Collisions;
}

void dae::ColliderComponent::ClearCollisions()
{
	m_Collisions.clear();
}

