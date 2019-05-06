#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"
#include "BaseCommand.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene()
{
	for (auto pGameObject : mObjects)
	{
		delete pGameObject;
	}
};

void dae::Scene::Add(GameObject* object)
{
	mObjects.push_back(object);
}


void dae::Scene::Initialize()
{
	for (auto gameObject : mObjects)
	{
		gameObject->Initialize();
	}
}

void dae::Scene::Update(float deltaTime)
{
	InputManager* pInputManager = &InputManager::GetInstance();
	size_t nrOfControllers = pInputManager->GetMaxNrOfControllers();
	for (size_t i = 0; i < nrOfControllers; i++)
	{
		BaseCommand* pCommand = pInputManager->HandleInput(i);
		if (pCommand) { pCommand->Execute(); }
	}
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

