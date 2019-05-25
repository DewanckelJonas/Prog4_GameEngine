#include "pch.h"
#include "DigDugScene.h"
#include <GameObject.h>
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <SpriteComponent.h>
#include <InputManager.h>
#include <TextComponent.h>
#include <Font.h>
#include "DigDugLevelComponent.h"
#include "DigDugPrefabs.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"


void DigDugScene::Initialize()
{
	auto liveDisplay = std::make_shared<dae::GameObject>();
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 50);
	liveDisplay->AddComponent(std::make_shared<dae::TextComponent>("Lives", font));
	auto livesComp = std::make_shared<LivesComponent>(3);
	liveDisplay->AddComponent(livesComp);
	liveDisplay->AddComponent(std::make_shared<LivesDisplayComponent>());
	liveDisplay->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 10, 0)));

	m_Level = std::make_shared<dae::GameObject>();
	m_Level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 0.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("Level1.gr", 400.f, 400.f, livesComp);
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

	Add(liveDisplay);

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
