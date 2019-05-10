#pragma once
#include "Shapes.h"
namespace dae
{
	struct Collision
	{
		ColliderComponent* otherCollider;
		Rect intersection;
	};
	class ColliderComponent
	{
	public:
		ColliderComponent(const Rect& shape, const std::string& tag);
		void CheckCollision(ColliderComponent& collider);
	private:
		Rect m_Shape;
		std::string m_Tag;
		std::vector<Collision> m_Collisions;
	};
}

