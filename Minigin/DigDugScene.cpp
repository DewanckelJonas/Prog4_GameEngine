#include "MiniginPCH.h"
#include "DigDugScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "PlayerController.h"

void DigDugScene::Initialize()
{
	m_Player = new dae::GameObject();
	m_Player->AddComponent(new dae::TransformComponent(glm::vec3(0.f, 0.f, 0.f)));
	m_Player->AddComponent(new dae::SpriteComponent("../Data/Player.png", 2, 8));
	Add(m_Player);

	m_Player1 = new dae::GameObject();
	m_Player1->AddComponent(new dae::TransformComponent(glm::vec3(0.f, 200.f, 0.f)));
	m_Player1->AddComponent(new dae::SpriteComponent("../Data/Player.png", 2, 8));
	Add(m_Player1);

	m_PlayerController = dae::InputManager::GetInstance().GetPlayerControllers(0);
	m_PlayerController->AddCommand(dae::ControllerButton::ButtonA ,std::make_shared<dae::MoveCmd>(glm::vec3{ 1, 0, 0 }, 5.f));

	

	Scene::Initialize();
}

void DigDugScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonB))
	{
		m_PlayerController->Posses(m_Player);
	}
	else
	{
		m_PlayerController->Posses(m_Player1);
	}
}

DigDugScene::~DigDugScene()
{
}
