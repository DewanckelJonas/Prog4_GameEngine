#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"


void dae::SceneManager::AddScene(Scene * pScene, const std::string & name)
{
	if (m_spScenes[name] != nullptr)
	{
		std::cout << "Error Scene with that name already exists" << std::endl;
		return;
	}
	m_spScenes[name] = std::shared_ptr<Scene>(pScene);
	if (!m_spCurrentScene)
		m_spCurrentScene = m_spScenes[name];
}

void dae::SceneManager::Initialize()
{
	m_spCurrentScene->Initialize();
}

void dae::SceneManager::Update(float deltaTime)
{
	m_spCurrentScene->UpdateAI();
	if(m_NextScene)
	{
		SwapScene();
	}
	m_spCurrentScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_spCurrentScene->Render();
	m_HasFinishedGameLoop = true;
}

void dae::SceneManager::SetActiveScene(const std::string & name)
{
	if (m_spScenes[name])
	{
		m_NextScene = m_spScenes[name];
	}
	else
	{
		std::cout << "Level: " << name << " does not exist no new active scene set!" << std::endl;
	}
}

void dae::SceneManager::SwapScene()
{
	for (size_t i = 0; i < dae::InputManager::GetInstance().GetMaxNrOfControllers(); i++)
	{
		dae::InputManager::GetInstance().ClearCommands(i);
	}
	m_spCurrentScene->CleanUp();
	m_spCurrentScene = m_NextScene;
	m_spCurrentScene->Initialize();
	m_NextScene = std::shared_ptr<Scene>();
}

