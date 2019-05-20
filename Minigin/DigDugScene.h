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
	std::shared_ptr<dae::GameObject> m_Player;
	std::shared_ptr<dae::GameObject> m_Player1;
	std::shared_ptr<dae::GameObject> m_Level;
};

