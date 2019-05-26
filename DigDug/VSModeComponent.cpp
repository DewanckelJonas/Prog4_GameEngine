#include "pch.h"
#include "VSModeComponent.h"
#include "TransformComponent.h"
#include "DigDugPrefabs.h"
#include "InputManager.h"
#include "PlayerController.h"
#include <GameObject.h>
#include <SubjectComponent.h>
#include "LivesComponent.h"
#include <SceneManager.h>
#include <Scene.h>

VSModeComponent::VSModeComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel, const std::weak_ptr<LivesComponent>& fygarLives)
	:m_wpLevel(wpLevel)
	,m_wpFygarLives(fygarLives)
{
}

VSModeComponent::~VSModeComponent()
{
}

void VSModeComponent::OnNotify(const std::string & event, const std::weak_ptr<dae::GameObject>& subject)
{
	if (event == "Died") 
	{
		auto pos = m_wpLevel.lock()->GetPlayerSpawnPosition(0);
		subject.lock()->GetComponent<dae::TransformComponent>().lock()->SetPosition(glm::vec3{ pos.x, pos.y, 0 });
	}
	if(event == "Popped")
	{
		auto fygar = DigDugPrefabs::CreateFygarPlayer(1, m_wpLevel);
		dae::InputManager::GetInstance().GetPlayerControllers(1)->Posses(fygar);
		fygar->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(m_wpFygarLives);
		dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(fygar);
	}
	if (event == "GameOver") 
	{
		//restart level
		auto sceneName = dae::SceneManager::GetInstance().GetActiveScene().lock()->GetName();
		dae::SceneManager::GetInstance().SetActiveScene(sceneName);
	}
}
