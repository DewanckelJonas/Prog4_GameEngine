#pragma once
#include "AIController.h"
#include "DigDugEnemyComponent.h"
class PookaAI final : public dae::AIController
{
public:
	PookaAI(const std::weak_ptr<dae::GameObject>& pActor) :AIController(pActor) {};
	virtual ~PookaAI() = default;
	void Initialize();
	std::weak_ptr<dae::BaseCommand> Update(float deltaTime);
private:
	glm::vec2 m_Target{};
	float m_TimeBetweenDirChange{ 0.f };
	const float m_MinTimeBetweenDirChange{ 0.5f };
	float m_GhostDuration{ 0.f };
	const float m_MinGhostDuration{ 1.f };
	int m_NrFailedPaths{};
	const int m_NrFailsBeforeGhost{3};
	std::weak_ptr<const DigDugLevelComponent> m_wpLevel;
	float m_MinTimeBetweenFire = 5.f;
	float m_TimeTillFire = 0.f;
	const int m_FireActivationRange = 3;
	std::shared_ptr<PookaMoveCmd> m_spMove = std::make_shared<PookaMoveCmd>(glm::vec2{ 1, 0 });
	std::shared_ptr<PookaGhostCommand> m_spGhostCommand = std::make_shared<PookaGhostCommand>();
	std::shared_ptr<EnemyFireCommand> m_spFireCommand = std::make_shared<EnemyFireCommand>();
};

