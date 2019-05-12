#pragma once
#include "IState.h"

namespace dae { class TransformComponent; }
class DigDugPlayerComponent;
class DigDugIdleState final : public dae::IState
{
public:
	DigDugIdleState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override {};
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	DigDugPlayerComponent* m_pPlayerComponent;
};

class DigDugMoveState final : public dae::IState
{
public:
	DigDugMoveState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override;
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	DigDugPlayerComponent* m_pPlayerComponent;
	dae::TransformComponent* m_pTransformComponent;
	glm::vec2 prevForward{ 0,1 };
	float m_MovementSpeed{ 20 };
};

class DigDugPumpState final : public dae::IState
{
public:
	DigDugPumpState() {};
	void Enter(dae::GameObject* ) override {};
	void Exit(dae::GameObject* ) override {};
	IState* Update(dae::GameObject*, float ) override { return nullptr; };
private:
	DigDugPlayerComponent* m_pPlayerComponent;
};

class DigDugDyingState final : public dae::IState
{
public:
	DigDugDyingState() {};
	void Enter(dae::GameObject* ) override {};
	void Exit(dae::GameObject* ) override {};
	IState* Update(dae::GameObject*, float ) override { return nullptr; };

};