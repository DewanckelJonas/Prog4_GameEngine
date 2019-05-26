#include "pch.h"
#include "SPModeComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"

SPModeComponent::SPModeComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel)
	:m_wpLevel(wpLevel)
{
}

SPModeComponent::~SPModeComponent()
{
}

void SPModeComponent::OnNotify(const std::string & event, const std::weak_ptr<dae::GameObject>& subject)
{
	if(event == "GameOver")
	{
		//restart level
		auto sceneName = dae::SceneManager::GetInstance().GetActiveScene().lock()->GetName();
		dae::SceneManager::GetInstance().SetActiveScene(sceneName);
	}
	if(event == "Died")
	{
		auto pos = m_wpLevel.lock()->GetPlayerSpawnPosition(0);
		subject.lock()->GetComponent<dae::TransformComponent>().lock()->SetPosition(glm::vec3{pos.x, pos.y, 0});
	}
}

void SPModeComponent::Update(float)
{
	if(m_wpLevel.lock()->GetNrOfRemainingEnemies() <= 0)
	{
		m_wpLevel.lock()->Load("../Data/Level2.gr");
	}
}


