#pragma once
#include <Scene.h>
#include <GameObject.h>
class DigDugVersusScene final : public dae::Scene
{
public:
	explicit DigDugVersusScene() : Scene("DigDugVersusScene") {};
	void Initialize() override;
	void Update(float deltaTime) override;
	~DigDugVersusScene() = default;
private:
};