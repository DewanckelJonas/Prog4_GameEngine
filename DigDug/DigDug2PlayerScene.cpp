#include "pch.h"
#include "DigDug2PlayerScene.h"


#include "pch.h"
#include "DigDug2PlayerScene.h"
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
#include "SPModeComponent.h"
#include <FPSComponent.h>



void DigDug2PlayerScene::Initialize()
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

	auto fpsDisplay = std::make_shared<dae::GameObject>();
	fpsDisplay->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(400, 300, -1.f)));
	fpsDisplay->AddComponent(std::make_shared<dae::TextComponent>("Fps", font));
	fpsDisplay->AddComponent(std::make_shared<dae::FPSComponent>());
	Add(fpsDisplay);

	auto level = std::make_shared<dae::GameObject>();
	level->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3(0.f, 0.f, 1.f)));
	auto levelComp = std::make_shared<DigDugLevelComponent>("../Data/Level1.gr", 400.f, 400.f, scoreDisplay);

	level->AddComponent(levelComp);

	auto gameMode = std::make_shared<dae::GameObject>();
	auto gameModeComp = std::make_shared<SPModeComponent>(levelComp);
	gameMode->AddComponent(gameModeComp);
	Add(gameMode);

	liveDisplay->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);

	auto digdug = DigDugPrefabs::CreateDigDug(0, levelComp);
	digdug->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(livesComp);
	digdug->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);

	auto digdug2 = DigDugPrefabs::CreateDigDug(1, levelComp);
	digdug2->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(livesComp);
	digdug2->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(gameModeComp);

	Add(level);
	Add(digdug);
	Add(digdug2);
	levelComp->AddPlayer(digdug);
	levelComp->AddPlayer(digdug2);
	Add(liveDisplay);
	Add(scoreDisplay);
	Scene::Initialize();
}

void DigDug2PlayerScene::Update(float deltaTime)
{
	if(dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonX))
	{
		dae::SceneManager::GetInstance().SetActiveScene("GameSelectScene");
	}
	Scene::Update(deltaTime);
}
