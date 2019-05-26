#include "pch.h"
#include "GameSelectScene.h"
#include <InputManager.h>
#include <SceneManager.h>
#include <TextComponent.h>
#include <TransformComponent.h>
#include <Font.h>

void GameSelectScene::Initialize()
{
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 30);
	auto instructions = std::make_shared<dae::GameObject>();
	instructions->AddComponent(std::make_shared<dae::TransformComponent>(glm::vec3{ 20.f, 200.f, 0.f }));
	instructions->AddComponent(std::make_shared<dae::TextComponent>("Up: P1, Down: P2, Right: VS, Left: LevelEdit", font));
	Add(instructions);
	Scene::Initialize();
}

void GameSelectScene::Update(float deltaTime)
{

	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DpadUp))
	{
		dae::SceneManager::GetInstance().SetActiveScene("DigDug1PlayerScene");
	}
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DpadDown))
	{
		dae::SceneManager::GetInstance().SetActiveScene("DigDug2PlayerScene");
	}
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DpadRight))
	{
		dae::SceneManager::GetInstance().SetActiveScene("DigDugVersusScene");
	}
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::DpadLeft))
	{
		dae::SceneManager::GetInstance().SetActiveScene("DigDugLevelEditScene");
	}
	Scene::Update(deltaTime);
}
