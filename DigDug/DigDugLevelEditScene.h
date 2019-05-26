#pragma once
#include "Scene.h"
#include "GameObject.h"
class DigDugLevelEditScene final : public dae::Scene
{
public:
	explicit DigDugLevelEditScene() : Scene("DigDugLevelEditScene") {};
	void Initialize() override;
	void Update(float deltaTime) override;
	~DigDugLevelEditScene() = default;
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

