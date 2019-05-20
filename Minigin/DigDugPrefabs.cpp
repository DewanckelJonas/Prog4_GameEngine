#include "MiniginPCH.h"
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
#include "PookaAI.h"
#include "DigDugPlayerComponent.h"
#include "InputManager.h"
#include "PlayerController.h"


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

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreatePooka(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto pooka =std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	pooka->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Enemy"));
	pooka->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	pooka->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/PookaWalk.png", 1, 2, wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight()));
	pooka->AddComponent(std::make_shared<PookaComponent>(wpLevel));
	std::shared_ptr<PookaAI> pookaAI = std::make_shared<PookaAI>(pooka);
	dae::AISystem::GetInstance().AddAIController(pookaAI);
	return pooka;
}

std::shared_ptr<dae::GameObject> DigDugPrefabs::CreateDigDug(int playerIndex, const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto player = std::make_shared<dae::GameObject>();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	player->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	player->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/DigDug.png", 1, 2, 20.f, 20.f));
	player->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2{0.f,0.f }, 19.f, 19.f }, "Player"));
	player->AddComponent(std::make_shared<DigDugPlayerComponent>(wpLevel));

	auto playerController = dae::InputManager::GetInstance().GetPlayerControllers(playerIndex);
	playerController->AddCommand(dae::ControllerButton::DpadRight, std::make_shared<DigDugMoveCmd>(glm::vec2{ 1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadLeft, std::make_shared<DigDugMoveCmd>(glm::vec2{ -1, 0 }));
	playerController->AddCommand(dae::ControllerButton::DpadUp, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, -1 }));
	playerController->AddCommand(dae::ControllerButton::DpadDown, std::make_shared<DigDugMoveCmd>(glm::vec2{ 0, 1 }));
	playerController->AddCommand(dae::ControllerButton::ButtonA, std::make_shared<DigDugPumpCommand>());
	playerController->Posses(player);

	return player;
}