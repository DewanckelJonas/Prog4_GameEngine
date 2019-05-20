#include "MiniginPCH.h"
#include "PookaAI.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"

void PookaAI::Initialize()
{
	SetActor(m_spMove);
	SetActor(m_spGhostCommand);
	m_wpLevel = GetActor().lock()->GetComponent<PookaComponent>().lock()->GetLevel();
}

std::weak_ptr<dae::BaseCommand> PookaAI::Update(float deltaTime)
{
	auto pos = GetActor().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	//float sqDistanceTraveled = movementVec.x * movementVec.x + movementVec.y * movementVec.y;

	unsigned short row, col;
	auto spLevel = m_wpLevel.lock();
	spLevel->GetTileRowCol(pos, row, col);
	auto playerPos = spLevel->GetClosestPlayerPosition(pos);
	bool isGhost = GetActor().lock()->GetComponent<PookaComponent>().lock()->IsGhost();

	if (m_NrFailedPaths >= m_NrFailsBeforeGhost && !isGhost)
	{
		return m_spGhostCommand;
	}

	if (isGhost)
	{
		m_NrFailedPaths = 0;
		m_GhostDuration += deltaTime;

		if (playerPos.x < pos.x)
		{
			m_spMove->SetDirection(glm::vec2{ -1, 0 });
		}
		if (playerPos.x > pos.x)
		{
			m_spMove->SetDirection(glm::vec2{ 1, 0 });
		}
		if (playerPos.y < pos.y)
		{
			m_spMove->SetDirection(glm::vec2{ 0, -1 });
		}
		if (playerPos.y > pos.y)
		{
			m_spMove->SetDirection(glm::vec2{ 0, 1 });
		}
		if (!spLevel->GetTile(row, col).lock()->IsSolid() && m_GhostDuration > m_MinGhostDuration)
		{
			m_GhostDuration = 0.f;
			return m_spGhostCommand;
		}
	}

	m_TimeBetweenDirChange -= deltaTime;

	if (m_TimeBetweenDirChange < 0.f)
	{
		if(abs(m_spMove->GetDirection().y) > 0.f)
		{
			if (playerPos.x < pos.x)
			{
				if (!spLevel->GetTile(row, col - 1).lock()->IsSolid())
				{
					m_spMove->SetDirection(glm::vec2{ -1, 0 });
					m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				}
			}
			else
			{
				if (!spLevel->GetTile(row, col + 1).lock()->IsSolid() || isGhost)
				{
					m_spMove->SetDirection(glm::vec2{ 1, 0 });
					m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				}
			}
		}
		else
		{
			if (playerPos.y < pos.y)
			{
				if (!spLevel->GetTile(row - 1, col).lock()->IsSolid())
				{
					m_spMove->SetDirection(glm::vec2{ 0, -1 });
					m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				}
			}
			else
			{
				if (!spLevel->GetTile(row+1, col).lock()->IsSolid())
				{ 
					m_spMove->SetDirection(glm::vec2{ 0, 1 });
					m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				}
			}
		}
	}

	if (!isGhost && m_TimeBetweenDirChange < 0.f)
	{
		if (abs(m_spMove->GetDirection().y) > 0)
		{
			if (spLevel->GetTile(row - 1, col).lock()->IsSolid())
			{
				++m_NrFailedPaths;
				m_spMove->SetDirection(glm::vec2{ 0, 1 });
				m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				return m_spMove;
			}
			if (spLevel->GetTile(row + 1, col).lock()->IsSolid())
			{
				++m_NrFailedPaths;
				m_spMove->SetDirection(glm::vec2{ 0,  -1 });
				m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				return m_spMove;
			}

		}
		if (abs(m_spMove->GetDirection().x) > 0)
		{
			if (spLevel->GetTile(row, col + 1).lock()->IsSolid())
			{
				++m_NrFailedPaths;
				m_spMove->SetDirection(glm::vec2{ -1, 0 });
				m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				return m_spMove;
			}
			if (spLevel->GetTile(row, col - 1).lock()->IsSolid())
			{
				++m_NrFailedPaths;
				m_spMove->SetDirection(glm::vec2{ 1, 0 });
				m_TimeBetweenDirChange = m_MinTimeBetweenDirChange;
				return m_spMove;
			}

		}
	}
	return m_spMove;
}
