#include "MiniginPCH.h"
#include "DigDugPrefabs.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "PumpComponent.h"
#include "DigDugLevelComponent.h"


dae::GameObject* DigDugPrefabs::CreatePump(const glm::vec2& position, DigDugLevelComponent* pLevel)
{
	auto pump = new dae::GameObject();
	pump->AddComponent(new dae::TransformComponent(glm::vec3(position.x, position.y, 0.f)));
	pump->AddComponent(new dae::ColliderComponent(dae::Rect{ glm::vec2(0.1f, 0.f), pLevel->GetTileWidth(), pLevel->GetTileHeight() }, "Pump"));
	pump->AddComponent(new dae::TextureComponent("Pump.png", false));
	pump->AddComponent(new PumpComponent(60.f, 2.f, { 1, 0 }, pLevel));
	return pump;
}
