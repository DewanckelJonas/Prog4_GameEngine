#include "MiniginPCH.h"
#include "CollisionSystem.h"
#include "ColliderComponent.h"

void dae::CollisionSystem::AddCollider(ColliderComponent * pCollider)
{
	m_pColliders.push_back(pCollider);
}

void dae::CollisionSystem::RemoveCollider(ColliderComponent * pCollider)
{
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		if(m_pColliders[i] == pCollider)
		{
			m_pColliders[i] = m_pColliders.back();
			m_pColliders.pop_back();
			--i;
		}
	}
}

void dae::CollisionSystem::Update()
{
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		m_pColliders[i]->ClearCollisions();
	}
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		for (size_t j = i; j < m_pColliders.size(); j++)
		{
			m_pColliders[i]->CheckCollision(*m_pColliders[j]);
		}
	}
}
