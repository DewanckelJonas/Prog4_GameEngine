#pragma once
#pragma once
#include <Scene.h>
#include <GameObject.h>
class GameSelectScene final : public dae::Scene
{
public:
	explicit GameSelectScene() : Scene("GameSelectScene") {};
	void Initialize() override;
	void Update(float) override;
	~GameSelectScene() = default;
private:
};

