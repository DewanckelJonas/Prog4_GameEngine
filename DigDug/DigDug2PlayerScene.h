#pragma once
#include <Scene.h>
#include <GameObject.h>
class DigDug2PlayerScene final : public dae::Scene
{
public:
	explicit DigDug2PlayerScene() : Scene("DigDug2PlayerScene") {};
	void Initialize() override;
	~DigDug2PlayerScene() = default;
	void Update(float deltaTime) override;
private:
};


