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
#include "SubjectComponent.h"
#include "ScoreComponent.h"


void DigDugScene::Initialize()
{
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 30);
	auto liveDisplay = std::make_shared<dae::GameObject>();
	liveDisplay->AddComponent(std::make_shared<dae::TextComponent>("Lives", font));
	auto livesComp = std::make_shared<LivesComponent>(3);
	liveDisplay->AddComponent(livesComp);
	liveDisplay->AddComponent(std::make_shared<LivesDisplayComponent>());
	liveDisplay->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 10, 0)));
	liveDisplay->AddComponent(std::make_shared<dae::SubjectComponent>());

	auto scoreDisplay = std::make_shared<dae::GameObject>();
	scoreDisplay->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 200, 0)));
	scoreDisplay->AddComponent(std::make_shared<dae::TextComponent>("Score", font));
	auto scoreComp = std::make_shared<ScoreComponent>();
	scoreDisplay->AddComponent(scoreComp);

	m_LevelEditSelection = std::make_shared<dae::GameObject>();
	m_LevelEditSelection->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 300, 0)));
	m_LevelEditSelection->AddComponent(std::make_shared<dae::TextComponent>("Air", font));
	Add(m_LevelEditSelection);

	m_Level = std::make_shared<dae::GameObject>();
	m_Level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 0.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("Level1.gr", 400.f, 400.f, liveDisplay, scoreDisplay);
	
	m_Level->AddComponent(levelComp);
	Add(m_Level);


	Add(liveDisplay);
	Add(scoreDisplay);
	Scene::Initialize();
	
}

void DigDugScene::Update(float deltaTime)
{

	Scene::Update(deltaTime);
	if (dae::InputManager::GetInstance().IsMouseButtonReleased(dae::MouseButton::Left)) 
	{
		switch (m_SelectedType)
		{
		case Air:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::Air);
			break;
		case Ground1:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::GroundL1);
			break;
		case Ground2:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::GroundL2);
			break;
		case Ground3:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::GroundL3);
			break;
		case Ground4:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetTile(dae::InputManager::GetInstance().GetMousePosition(), DigDugLevelComponent::TileType::GroundL4);
			break;
		case Pooka:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->AddPookaSpawnPosition(dae::InputManager::GetInstance().GetMousePosition());
			break;
		case Fygar:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->AddFygarSpawnPosition(dae::InputManager::GetInstance().GetMousePosition());
			break;
		case Rock:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->AddRockSpawnPosition(dae::InputManager::GetInstance().GetMousePosition());
			break;
		case ClearPookas:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->ClearPookaSpawnPositions();
			break;
		case ClearFygars:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->ClearFygarSpawnPositions();
			break;
		case ClearRocks:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->ClearRockSpawnPositions();
			break;
		case Player1Pos:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetPlayerSpawnPosition(0, dae::InputManager::GetInstance().GetMousePosition());
			break;
		case Player2Pos:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetPlayerSpawnPosition(1, dae::InputManager::GetInstance().GetMousePosition());
			break;
		case Player3Pos:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetPlayerSpawnPosition(2, dae::InputManager::GetInstance().GetMousePosition());
			break;
		case Player4Pos:
			m_Level->GetComponent<DigDugLevelComponent>().lock()->SetPlayerSpawnPosition(3, dae::InputManager::GetInstance().GetMousePosition());
			break;
		default:
			break;
		}
	}
	if (dae::InputManager::GetInstance().IsMouseButtonReleased(dae::MouseButton::Right))
	{
		int objectNr = int(m_SelectedType);
		++objectNr;
		m_SelectedType = LevelEditType(objectNr % 15);
		switch (m_SelectedType)
		{
		case Air:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Air");
			break;
		case Ground1:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Ground1");
			break;
		case Ground2:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Ground2");
			break;
		case Ground3:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Ground3");
			break;
		case Ground4:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Ground4");
			break;
		case Pooka:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Pooka");
			break;
		case Fygar:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Fygar");
			break;
		case Rock:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Rock");
			break;
		case ClearPookas:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Clear Pookas");
			break;
		case ClearFygars:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Clear fygars");
			break;
		case ClearRocks:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Clear rocks");
			break;
		case Player1Pos:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Player 1 Position");
			break;
		case Player2Pos:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Player 2 Position");
			break;
		case Player3Pos:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Player 3 Position");
			break;
		case Player4Pos:
			m_LevelEditSelection->GetComponent<dae::TextComponent>().lock()->SetText("Player 4 Position");
			break;

		default:
			break;
		}
	}
	if (dae::InputManager::GetInstance().IsMouseButtonReleased(dae::MouseButton::Middle))
	{
		m_Level->GetComponent<DigDugLevelComponent>().lock()->Save("Level1.gr");
	}
	
}

