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
	object->Initialize();
	mObjects.push_back(object);
}


void dae::Scene::Initialize()
{
}

void dae::Scene::Update(float deltaTime)
{
	InputManager* pInputManager = &InputManager::GetInstance();
	size_t nrOfControllers = pInputManager->GetMaxNrOfControllers();
	for (size_t i = 0; i < nrOfControllers; i++)
	{
		auto spCommand = pInputManager->HandleInput(i);
		if (spCommand) { spCommand->Execute(); }
	}
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}
	for (int i = 0; i < int(mObjects.size()); i++)
	{
		if(mObjects[i]->IsDestroyed())
		{
			delete mObjects[i];
			mObjects[i] = mObjects.back();
			mObjects.pop_back();
			--i;
		}
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

