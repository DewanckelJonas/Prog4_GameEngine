#include "pch.h"
#include "DigDugVersusScene.h"
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
#include "VSModeComponent.h"
#include <FPSComponent.h>

void DigDugVersusScene::Initialize()
{
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 30);
	auto liveDisplayP1 = std::make_shared<dae::GameObject>();
	liveDisplayP1->AddComponent(std::make_shared<dae::TextComponent>("Lives", font));
	auto livesComp = std::make_shared<LivesComponent>(3);
	liveDisplayP1->AddComponent(livesComp);
	liveDisplayP1->AddComponent(std::make_shared<LivesDisplayComponent>());
	liveDisplayP1->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 10, 0)));
	liveDisplayP1->AddComponent(std::make_shared<dae::SubjectComponent>());

	auto liveDisplayP2 = std::make_shared<dae::GameObject>();
	liveDisplayP2->AddComponent(std::make_shared<dae::TextComponent>("Lives", font));
	auto livesComp2 = std::make_shared<LivesComponent>(3);
	liveDisplayP2->AddComponent(livesComp2);
	liveDisplayP2->AddComponent(std::make_shared<LivesDisplayComponent>());
	liveDisplayP2->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 100, 0)));
	liveDisplayP2->AddComponent(std::make_shared<dae::SubjectComponent>());

	auto fpsDisplay = std::make_shared<dae::GameObject>();
	fpsDisplay->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 300, -1.f)));
	fpsDisplay->AddComponent(std::make_shared<dae::TextComponent>("Fps", font));
	fpsDisplay->AddComponent(std::make_shared<dae::FPSComponent>());
	Add(fpsDisplay);

	auto level = std::make_shared<dae::GameObject>();
	level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 1.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("../Data/LevelVS.gr", 400.f, 400.f);

	level->AddComponent(levelComp);

	auto gameMode = std::make_shared<dae::GameObject>();
	auto gameModeComp = std::make_shared<VSModeComponent>(levelComp, livesComp2);
	gameMode->AddComponent(gameModeComp);
	Add(gameMode);

	liveDisplayP1->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);
	liveDisplayP2->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);

	auto digdug = DigDugPrefabs::CreateDigDug(0, levelComp);
	digdug->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(livesComp);
	digdug->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);

	auto fygar = DigDugPrefabs::CreateFygarPlayer(1, levelComp);
	fygar->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(livesComp2);
	fygar->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);


	Add(level);
	Add(digdug);
	Add(fygar);
	levelComp->AddPlayer(digdug);
	levelComp->AddPlayer(fygar);
	Add(liveDisplayP1);
	Add(liveDisplayP2);
	Scene::Initialize();
}

void DigDugVersusScene::Update(float deltaTime)
{
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonX))
	{
		dae::SceneManager::GetInstance().SetActiveScene("GameSelectScene");
	}
	Scene::Update(deltaTime);
}
