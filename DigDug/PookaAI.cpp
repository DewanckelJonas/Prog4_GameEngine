#include "pch.h"
#include "PookaAI.h"
#include "TransformComponent.h"
#include "DigDugLevelComponent.h"
#include "FygarComponent.h"

void PookaAI::Initialize()
{
	SetActor(m_spMove);
	SetActor(m_spGhostCommand);
	SetActor(m_spFireCommand);
	m_wpLevel = GetActor().lock()->GetComponent<DigDugEnemyComponent>().lock()->GetLevel();
}

std::weak_ptr<dae::BaseCommand> PookaAI::Update(float deltaTime)
{
	//TODO: Split this mess up into a statemachine and functions.
	auto pos = GetActor().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	//float sqDistanceTraveled = movementVec.x * movementVec.x + movementVec.y * movementVec.y;

	unsigned short row, col;
	auto spLevel = m_wpLevel.lock();
	spLevel->GetTileRowCol(pos, row, col);
	bool isGhost = GetActor().lock()->GetComponent<DigDugEnemyComponent>().lock()->IsGhost();
	if(!isGhost)
	{
		auto playerPos = spLevel->GetClosestPlayerPosition(pos);
		m_Target = spLevel->GetNearestTileCenter(playerPos);

		m_TimeTillFire += deltaTime;
		if(m_TimeTillFire > m_MinTimeBetweenFire && GetActor().lock()->GetComponent<FygarComponent>().lock())
		{
			unsigned short playerRow, playerCol;
			spLevel->GetTileRowCol(playerPos, playerRow, playerCol);
			if(abs(m_spMove->GetDirection().x) > 0.f)
			{
				if(playerRow == row) //is on the same row as the player
				{
					if(abs(playerCol - col) < m_FireActivationRange) //is in range to fire
					{
						bool hasLineOfSight = true;
						if(playerCol > col)
						{
							for (unsigned short i = col+1; i < playerCol; i++)
							{
								if (spLevel->GetTile(row, i).lock()->IsSolid()) { hasLineOfSight = false; }
							}
						}else
						{
							for (unsigned short i = playerCol + 1; i < col; i++)
							{
								if (spLevel->GetTile(row, i).lock()->IsSolid()) { hasLineOfSight = false; }
							}
						}
						if(hasLineOfSight)
						{
							//m_TimeTillFire = 0;
							return m_spFireCommand;
						}
					}
				}
			}
			else
			{
				if (playerCol == col) //is on the same col as the player
				{
					if (abs(playerRow - row) < m_FireActivationRange) //is in range to fire
					{
						bool hasLineOfSight = true;
						if (playerRow > row)
						{
							for (unsigned short i = row + 1; i < playerRow; i++)
							{
								if (spLevel->GetTile(i, col).lock()->IsSolid()) { hasLineOfSight = false; }
							}
						}
						else
						{
							for (unsigned short i = playerCol + 1; i < col; i++)
							{
								if (spLevel->GetTile(i, col).lock()->IsSolid()) { hasLineOfSight = false; }
							}
						}
						if (hasLineOfSight)
						{
							//m_TimeTillFire = 0;
							return m_spFireCommand;
						}
					}
				}
			}
		}

	}

	if (m_NrFailedPaths >= m_NrFailsBeforeGhost && !isGhost)
	{
		return m_spGhostCommand;
	}

	if (isGhost)
	{
		m_NrFailedPaths = 0;
		m_GhostDuration += deltaTime;
		glm::vec2 dir;
		if (m_Target.x < pos.x)
		{
			dir.x = -1;
		}
		if (m_Target.x > pos.x)
		{
			dir.x = 1;
		}
		if (m_Target.y < pos.y)
		{
			dir.y = -1;
		}
		if (m_Target.y > pos.y)
		{
			dir.y = 1;
		}

		m_spMove->SetDirection(dir);
		if (!spLevel->GetTile(row, col).lock()->IsSolid() && m_GhostDuration > m_MinGhostDuration)
		{
			auto newPos = spLevel->GetNearestTileCenter(pos);
			if(abs(newPos.x - pos.x) > 0.01f && abs(newPos.y - pos.y) > 0.01f)
			{
				return m_spMove;
			}
			m_GhostDuration = 0.f;

			return m_spGhostCommand;
		}
	}

	m_TimeBetweenDirChange -= deltaTime;

	if (m_TimeBetweenDirChange < 0.f)
	{
		if(abs(m_spMove->GetDirection().y) > 0.f)
		{
			if (m_Target.x < pos.x)
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
			if (m_Target.y < pos.y)
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
