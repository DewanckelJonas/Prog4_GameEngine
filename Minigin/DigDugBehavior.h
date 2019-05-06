#pragma once
#include "IBehavior.h"
class TransformComponent;
class DigDugBehavior : public dae::IBehavior
{
public:
	DigDugBehavior();
	~DigDugBehavior();
	void Initialize(dae::GameObject* pObject) override;
	void Update(dae::GameObject* pObject, float deltaTime) override;

private:
	TransformComponent* m_pTransformComponent;
};

