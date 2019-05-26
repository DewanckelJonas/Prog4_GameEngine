#include "pch.h"
#include "DigDugPrefabs.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PumpComponent.h"
#include "DigDugLevelComponent.h"
#include "PookaComponent.h"
#include "AISystem.h"
#include "EnemyAI.h"
#include "DigDugPlayerComponent.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "FygarFireComponent.h"
#include "FygarComponent.h"
#include "RockComponent.h"
#include <SubjectComponent.h>
#include "ScoreComponent.h"


std::shared_ptr<dae::GameObject> DigDugPrefabs::CreatePump(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel)
{
	auto pump = std::make_shared<dae::GameObject>();
	auto transform = std::make_shared<dae::TransformComponent>(glm::vec3(position.x, position.y, 0.f));
	transform->SetRotation(atan2f(direction.y, direction.x)/3.14f*180.f);
	pump->AddComponent(transform);
	pump->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Pump"));
	pump->AddComponent(std::make_shared<dae::TextureComponent>("Pump.png", false));
	pump->AddComponent(std::make_shared<PumpComponent>(110.f, 0.6f, direction, wpLevel));
	return pump;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateFire(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel)
{
	auto fire = std::make_shared<dae::GameObject>();
	auto transform = std::make_shared<dae::TransformComponent>(glm::vec3(position.x, position.y, 0.f));
	transform->SetRotation(atan2f(direction.y, direction.x) / 3.14f*180.f);
	fire->AddComponent(transform);
	fire->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Fire"));
	fire->AddComponent(std::make_shared<dae::TextureComponent>("FygarFire.png", false));
	fire->AddComponent(std::make_shared<FygarFireComponent>(50.f, 1.f, direction, wpLevel));
	return fire;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreatePooka(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto pooka =std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	pooka->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Enemy"));
	pooka->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	pooka->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/PookaWalk.png", 1, 2, wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight()));
	pooka->AddComponent(std::make_shared<PookaComponent>(wpLevel));
	auto subject = std::make_shared<dae::SubjectComponent>();
	pooka->AddComponent(subject);
	std::shared_ptr<EnemyAI> enemyAI = std::make_shared<EnemyAI>(pooka);
	dae::AISystem::GetInstance().AddAIController(enemyAI);
	return pooka;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateFygar(const glm::vec2 & position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto fygar = std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	fygar->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Enemy"));
	fygar->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	fygar->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/FygarWalk.png", 1, 2, wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight()));
	fygar->AddComponent(std::make_shared<FygarComponent>(wpLevel));
	auto subject = std::make_shared<dae::SubjectComponent>();
	fygar->AddComponent(subject);
	std::shared_ptr<EnemyAI> enemyAI = std::make_shared<EnemyAI>(fygar);
	dae::AISystem::GetInstance().AddAIController(enemyAI);
	return fygar;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateFygarPlayer(int id, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto fygar = std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(wpLevel.lock()->GetPlayerSpawnPosition(id));
	fygar->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Enemy"));
	fygar->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	fygar->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/FygarWalk.png", 1, 2, wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight()));
	fygar->AddComponent(std::make_shared<FygarComponent>(wpLevel));
	auto subject = std::make_shared<dae::SubjectComponent>();
	fygar->AddComponent(subject);
	
	auto playerController = dae::InputManager::GetInstance().GetPlayerControllers(id);
	playerController->AddCommand(dae::ControllerButton::DpadRight, std::make_shared<EnemyMoveCmd>(glm::vec2{ 1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadLeft, std::make_shared<EnemyMoveCmd>(glm::vec2{ -1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadUp, std::make_shared<EnemyMoveCmd>(glm::vec2{ 0, -1 }));
	playerController->AddCommand(dae::ControllerButton::DpadDown, std::make_shared<EnemyMoveCmd>(glm::vec2{ 0, 1 }));
	playerController->AddCommand(dae::ControllerButton::ButtonA, std::make_shared<EnemyFireCommand>());
	playerController->AddCommand(dae::ControllerButton::ButtonB, std::make_shared<EnemyGhostCommand>());
	playerController->Posses(fygar);

	return fygar;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateRock(const glm::vec2 & position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto rock = std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	rock->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.f, 0.f), wpLevel.lock()->GetTileWidth() -1, wpLevel.lock()->GetTileHeight()-1 }, "Rock"));
	rock->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	auto textureComp = std::make_shared<dae::TextureComponent>("Rock.png");
	auto subject = std::make_shared<dae::SubjectComponent>();
	rock->AddComponent(subject);
	textureComp->SetTargetHeight(wpLevel.lock()->GetTileHeight());
	textureComp->SetTargetWidth(wpLevel.lock()->GetTileWidth());
	rock->AddComponent(textureComp);
	rock->AddComponent(std::make_shared<RockComponent>(wpLevel));
	return rock;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateDigDug(int playerIndex, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto player = std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(wpLevel.lock()->GetPlayerSpawnPosition(playerIndex));
	player->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	player->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/DigDug.png", 1, 2, 20.f, 20.f));
	player->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2{0.f,0.f }, 15.f, 15.f }, "Player"));
	player->AddComponent(std::make_shared<DigDugPlayerComponent>(wpLevel));
	player->AddComponent(std::make_shared<dae::SubjectComponent>());

	auto playerController = dae::InputManager::GetInstance().GetPlayerControllers(playerIndex);
	playerController->AddCommand(dae::ControllerButton::DpadRight, std::make_shared<DigDugMoveCmd>(glm::vec2{ 1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadLeft, std::make_shared<DigDugMoveCmd>(glm::vec2{ -1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadUp, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, -1 }));
	playerController->AddCommand(dae::ControllerButton::DpadDown, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, 1 }));
	playerController->AddCommand(dae::ControllerButton::ButtonA, std::make_shared<DigDugPumpCommand>());
	playerController->Posses(player);

	return player;
}