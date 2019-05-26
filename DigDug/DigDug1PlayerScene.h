#pragma once
#include <Scene.h>
#include <GameObject.h>
class DigDug1PlayerScene final : public dae::Scene
{
public:
	explicit DigDug1PlayerScene() : Scene("DigDug1PlayerScene") {};
	void Initialize() override;
	void Update(float deltaTime) override;
	~DigDug1PlayerScene() = default;
private:
};

