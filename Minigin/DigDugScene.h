#pragma once
#include "Scene.h"
namespace dae { class MoveCmd; class GameObject; class PlayerController; }
class DigDugScene final : public dae::Scene
{
public:
	explicit DigDugScene() : Scene("DigDugScene") {};
	void Initialize() override;
	void Update(float deltaTime) override;
	~DigDugScene();

	dae::PlayerController* m_PlayerController;
	dae::GameObject* m_Player;
	dae::GameObject* m_Player1;
};

