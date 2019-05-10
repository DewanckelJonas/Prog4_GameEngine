#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "CollisionSystem.h"

dae::ColliderComponent::ColliderComponent(const Rect & shape, const std::string& tag)
	:m_Shape{shape}
	,m_Tag{tag}
{
	CollisionSystem::GetInstance().AddCollider(this);
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

