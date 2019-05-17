#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

void dae::GameObject::Initialize()
{
	for (auto pComponent : m_spComponents)
	{
		pComponent->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime) 
{
	for(auto pComponent : m_spComponents)
	{
		pComponent->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{

	for (auto pComponent : m_spComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComponent)
{
	pComponent->m_GameObject = this;
	m_spComponents.push_back(pComponent);
}



