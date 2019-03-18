#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
	for (auto pComponent : m_pComponents)
	{
		delete pComponent;
	}
};

void dae::GameObject::Initialize()
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime) 
{
	for(auto pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{

	for (auto pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	pComponent->m_GameObject = this;
	m_pComponents.push_back(pComponent);
}


