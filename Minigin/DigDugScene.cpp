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

void DigDugScene::Initialize()
{
	m_Level = new dae::GameObject();
	m_Level->AddComponent(new dae::TransformComponent(glm::vec3(0.f, 0.f, 0.f)));
	auto levelComp = new DigDugLevelComponent("Level1.gr", 400, 400);
	m_Level->AddComponent(levelComp);
	Add(m_Level);

	m_Player = new dae::GameObject();
	auto spawnPos = levelComp->GetNearestTileCenter(glm::vec2{ 180.f, 20.f });
	m_Player->AddComponent(new dae::TransformComponent(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	m_Player->AddComponent(new dae::SpriteComponent("../Data/DigDug.png", 1, 2, 20.f, 20.f));
	m_Player->AddComponent(new DigDugPlayerComponent(levelComp));
	Add(m_Player);

	m_PlayerController = dae::InputManager::GetInstance().GetPlayerControllers(0);
	m_PlayerController->AddCommand(dae::ControllerButton::DpadRight ,std::make_shared<DigDugMoveCmd>(glm::vec2{ 1, 0 }));
	m_PlayerController->AddCommand(dae::ControllerButton::DpadLeft, std::make_shared<DigDugMoveCmd>(glm::vec2{ -1, 0 }));
	m_PlayerController->AddCommand(dae::ControllerButton::DpadUp, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, -1 }));
	m_PlayerController->AddCommand(dae::ControllerButton::DpadDown, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, 1 }));
	m_PlayerController->AddCommand(dae::ControllerButton::ButtonA, std::make_shared<DigDugPumpCommand>());

	m_PlayerController->Posses(m_Player);

	Scene::Initialize();
	
}

void DigDugScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Left)) 
	{
		m_Level->GetComponent<DigDugLevelComponent>()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::Ground);
	}
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Right))
	{
		m_Level->GetComponent<DigDugLevelComponent>()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::Air);
	}
	if (dae::InputManager::GetInstance().IsMouseButtonPressed(dae::MouseButton::Middle))
	{
		m_Level->GetComponent<DigDugLevelComponent>()->Save("Level1.gr");
	}
}

DigDugScene::~DigDugScene()
{
}
