#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "BaseCommand.h"
#include "TransformComponent.h"


dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene()
{
};

void dae::Scene::Add(std::shared_ptr<GameObject> spObject)
{
	spObject->Initialize();
	m_spObjects.push_back(spObject);
}


void dae::Scene::Initialize()
{
}

void dae::Scene::UpdateAI()
{
	std::vector<std::weak_ptr<BaseCommand>> aiCommands;
	if (m_wpAICommands.valid())
		aiCommands = m_wpAICommands.get();

	for (size_t i = 0; i < aiCommands.size(); i++)
	{
		aiCommands[i].lock()->Execute();
	}
}

void dae::Scene::Update(float deltaTime)
{
	InputManager* pInputManager = &InputManager::GetInstance();
	CollisionSystem* pCollisionSystem = &CollisionSystem::GetInstance();

	size_t nrOfControllers = pInputManager->GetMaxNrOfControllers();
	for (size_t i = 0; i < nrOfControllers; i++)
	{
		for(auto spCommand : pInputManager->HandleInput(i))
			if (spCommand) { spCommand->Execute(); }
	}

	for (size_t i{}; i < m_spObjects.size(); ++i)
	{
		if (!m_spObjects[i]->IsDestroyed())
		{
			m_spObjects[i]->Update(deltaTime);
		}
	}
	for (int i = 0; i < int(m_spObjects.size()); i++)
	{
		if(m_spObjects[i]->IsDestroyed())
		{
			m_spObjects[i] = m_spObjects.back();
			m_spObjects.pop_back();
			--i;
		}
	}
	pCollisionSystem->Update();

	AISystem* pAISystem = &AISystem::GetInstance();
	m_wpAICommands = std::async(&AISystem::Update, pAISystem, deltaTime);

	//Sort objects by depth
	std::sort(m_spObjects.begin(), m_spObjects.end(), [](const std::shared_ptr<dae::GameObject> obj1, const std::shared_ptr<dae::GameObject> obj2)
	{
		if (!obj1->GetComponent<dae::TransformComponent>().lock())
		{
			return true;
		}
		if (!obj2->GetComponent<dae::TransformComponent>().lock())
		{
			return false;
		}
		return (obj1->GetComponent<dae::TransformComponent>().lock()->GetPosition().z > obj2->GetComponent<dae::TransformComponent>().lock()->GetPosition().z);
	}
	);
}

void dae::Scene::Render() const
{
	
	for(const auto& spObject : m_spObjects)
	{
		spObject->Render();
	}
}

void dae::Scene::CleanUp()
{
	m_spObjects.clear();
}


