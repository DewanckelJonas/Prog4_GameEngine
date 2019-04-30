#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::AddScene(Scene * pScene, const std::string & name)
{
	if (!m_spScenes[name])
	{
		std::cout << "Error Scene with that name already exists" << std::endl;
		return;
	}
	m_spScenes[name] = std::shared_ptr<Scene>(pScene);
	if (!m_spCurrentScene)
		m_spCurrentScene = m_spScenes[name];
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
}

void dae::SceneManager::Update(float deltaTime)
{
	m_spCurrentScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_spCurrentScene->Render();
}

