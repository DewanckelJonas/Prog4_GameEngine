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


dae::GameObject* DigDugPrefabs::CreatePump(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel)
{
	auto pump = new dae::GameObject();
	auto transform = std::make_shared<dae::TransformComponent>(glm::vec3(position.x, position.y, 0.f));
	transform->SetRotation(atan2f(direction.y, direction.x)/3.14f*180.f);
	pump->AddComponent(transform);
	pump->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Pump"));
	pump->AddComponent(std::make_shared<dae::TextureComponent>("Pump.png", false));
	pump->AddComponent(std::make_shared<PumpComponent>(60.f, 2.f, direction, wpLevel));
	return pump;
}

dae::GameObject* DigDugPrefabs::CreatePooka(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel)
{
	auto pooka = new dae::GameObject();
	auto spawnPos = wpLevel.lock()->GetNearestTileCenter(position);
	pooka->AddComponent(std::make_shared<dae::ColliderComponent>(dae::Rect{ glm::vec2(0.1f, 0.f), wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight() }, "Enemy"));
	pooka->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(spawnPos.x, spawnPos.y, 0.f)));
	pooka->AddComponent(std::make_shared<dae::SpriteComponent>("../Data/PookaWalk.png", 1, 2, wpLevel.lock()->GetTileWidth(), wpLevel.lock()->GetTileHeight()));
	pooka->AddComponent(std::make_shared<PookaComponent>(wpLevel));
	return pooka;
}