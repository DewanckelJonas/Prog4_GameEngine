#include "MiniginPCH.h"
#include "DigDugScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"

void DigDugScene::Initialize()
{
	auto m_Player = new dae::GameObject();
	m_Player->AddComponent(new dae::TransformComponent(glm::vec3(0.f, 0.f, 0.f)));
	m_Player->AddComponent(new dae::SpriteComponent("../Data/Player.png", 2, 8));
	m_MoveRight = new dae::MoveCmd{ glm::vec3(1, 0, 0), 5 };
	m_MoveRight->SetActor(m_Player);
	dae::InputManager::GetInstance().SetCommand(dae::ControllerButton::ButtonA, m_MoveRight);
	Add(m_Player);

	auto m_Player1 = new dae::GameObject();
	m_Player1->AddComponent(new dae::TransformComponent(glm::vec3(0.f, 200.f, 0.f)));
	m_Player1->AddComponent(new dae::SpriteComponent("../Data/Player.png", 2, 8));
	m_MoveRight1 = new dae::MoveCmd{ glm::vec3(1, 0, 0), 5 };
	m_MoveRight1->SetActor(m_Player1);
	dae::InputManager::GetInstance().SetCommand(dae::ControllerButton::ButtonA, m_MoveRight1, 1);
	Add(m_Player1);

	Scene::Initialize();
}

DigDugScene::~DigDugScene()
{
	delete m_MoveRight;
	delete m_MoveRight1;
}
