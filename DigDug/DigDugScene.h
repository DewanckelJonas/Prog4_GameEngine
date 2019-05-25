#pragma once
#include "Scene.h"
#include "GameObject.h"
class DigDugScene final : public dae::Scene
{
public:
	explicit DigDugScene() : Scene("DigDugScene") {};
	void Initialize() override;
	void Update(float deltaTime) override;
	~DigDugScene() = default;
private:
	enum LevelEditType
	{
		Air,
		Ground1,
		Ground2,
		Ground3,
		Ground4,
		Pooka,
		Fygar,
		Rock,
		ClearPookas,
		ClearFygars,
		ClearRocks,
		Player1Pos,
		Player2Pos,
		Player3Pos,
		Player4Pos
	};
	LevelEditType m_SelectedType = Air;
	std::shared_ptr<dae::GameObject> m_Level;
	std::shared_ptr<dae::GameObject> m_LevelEditSelection;
};

