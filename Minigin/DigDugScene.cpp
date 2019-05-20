#include "MiniginPCH.h"
#include "DigDugScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "DigDugPlayerComponent.h"
#include "DigDugLevelComponent.h"
#include "ColliderComponent.h"
#include "PumpComponent.h"
#include "PookaComponent.h"
#include "DigDugPrefabs.h"


void DigDugScene::Initialize()
{
	m_Level = std::make_shared<dae::GameObject>();
	m_Level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 0.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("Level1.gr", 400.f, 400.f);
	m_Level->AddComponent(levelComp);
	Add(m_Level);

	/*m_Player = std::make_shared<dae::GameObject>();
	auto spawnPos = levelComp->GetNearestTileCenter(glm::vec2{ 180.f, 20.f });
	m_Player->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	m_Player->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/DigDug.png", 1, 2, 20.f, 20.f));
	m_Player->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2{0.f,0.f }, 19.f, 19.f }, "Player"));
	m_Player->AddComponent(std::make_shared<DigDugPlayerComponent>(levelComp));
	Add(m_Player);*/

	auto pooka = DigDugPrefabs::CreatePooka({ 180.f, 60.f }, levelComp);
	Add(pooka);

	pooka = DigDugPrefabs::CreatePooka({ 180.f, 80.f }, levelComp);
	Add(pooka);

	pooka = DigDugPrefabs::CreatePooka({ 180.f, 100.f }, levelComp);
	Add(pooka);

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
