#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class ColliderComponent;
	class CollisionSystem : public Singleton<CollisionSystem>
	{
	public:
		void AddCollider(ColliderComponent* pCollider);
		void RemoveCollider(ColliderComponent* pCollider);
		void Update();
	private:
		std::vector<ColliderComponent*> m_pColliders;
	};
}

