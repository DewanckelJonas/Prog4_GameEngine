#pragma once
#include "Scene.h"
namespace dae { class MoveCmd; }
class DigDugScene final : public dae::Scene
{
public:
	explicit DigDugScene() : Scene("DigDugScene") {};
	void Initialize() override;
	~DigDugScene();

	dae::MoveCmd* m_MoveRight;
	dae::MoveCmd* m_MoveRight1;
};

