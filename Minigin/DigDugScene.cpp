#include "MiniginPCH.h"
#include "DigDugScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "DigDugLevelComponent.h"
#include "DigDugPrefabs.h"


void DigDugScene::Initialize()
{
	m_Level = std::make_shared<dae::GameObject>();
	m_Level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 0.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("Level1.gr", 400.f, 400.f);
	m_Level->AddComponent(levelComp);
	Add(m_Level);

	/*auto pooka = DigDugPrefabs::CreatePooka({ 180.f, 60.f }, levelComp);
	Add(pooka);

	pooka = DigDugPrefabs::CreatePooka({ 180.f, 80.f }, levelComp);
	Add(pooka);*/

	auto fygar = DigDugPrefabs::CreateFygar({ 180.f, 100.f }, levelComp);
	Add(fygar);

	auto rock = DigDugPrefabs::CreateRock({ 180.f, 60.f }, levelComp);
	Add(rock);

	Scene::Initialize();
	
}

void DigDugScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Left)) 
	{
		m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::Ground);
	}
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Right))
	{
		m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::Air);
	}
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Middle))
	{
		m_Level->GetComponent<DigDugLevelComponent>().lock()->Save("Level1.gr");
	}
	
}

DigDugScene::~DigDugScene()
{
}
