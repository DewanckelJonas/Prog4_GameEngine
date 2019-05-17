#pragma once
#include "IState.h"

namespace dae { class TransformComponent; class SpriteComponent; }
class DigDugPlayerComponent;
class PookaComponent;
class PumpComponent;
class DigDugIdleState final : public dae::IState
{
public:
	DigDugIdleState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override {};
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	std::weak_ptr<DigDugPlayerComponent> m_pPlayerComponent;
};

class DigDugMoveState final : public dae::IState
{
public:
	DigDugMoveState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override;
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	std::weak_ptr<DigDugPlayerComponent> m_pPlayerComponent;
	std::weak_ptr<dae::TransformComponent> m_pTransformComponent;
	glm::vec2 m_PrevDirection{ 0,0 };
	float m_MovementSpeed{ 50 };
	float m_GridSnap{ 2.f };
};

class DigDugPumpState final : public dae::IState
{
public:
	DigDugPumpState() {};
	void Enter(dae::GameObject* ) override;
	void Exit(dae::GameObject* ) override {};
	IState* Update(dae::GameObject*, float ) override;
private:
	bool m_CanCancel = false;
	float m_ElapsedSec = 0.f;
	float m_TimeBetweenPumps = 0.6f;
	float m_CancelTime = 0.5f;
	std::weak_ptr<PumpComponent> m_pPump;
	std::weak_ptr<DigDugPlayerComponent> m_pPlayerComponent;
};

class DigDugDyingState final : public dae::IState
{
public:
	DigDugDyingState() {};
	void Enter(dae::GameObject* ) override {};
	void Exit(dae::GameObject* ) override {};
	IState* Update(dae::GameObject*, float ) override { return nullptr; };

};

class PookaMoveState final : public dae::IState
{
public:
	PookaMoveState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override {};
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	std::weak_ptr<PookaComponent> m_pPlayerComponent;
	std::weak_ptr<dae::TransformComponent> m_pTransformComponent;
	glm::vec2 m_PrevDirection{ 0,0 };
	float m_MovementSpeed{ 50 };
	float m_GridSnap{ 2.f };
};

class PookaIdleState final : public dae::IState
{
public:
	PookaIdleState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override {};
	IState* Update(dae::GameObject*, float deltaTime) override;
private:
	std::weak_ptr<PookaComponent> m_pPlayerComponent;
};

class PookaDyingState final : public dae::IState
{
public:
	PookaDyingState() {};
	void Enter(dae::GameObject*) override;
	void Exit(dae::GameObject*) override {};
	IState* Update(dae::GameObject*, float) override;
private:
	float m_ElapsedSec;
	float m_DeflateTime = 1.f;
	int m_Health = 3;
	const int m_MaxHealth = 3;
	std::weak_ptr<dae::SpriteComponent> m_pSpriteComp;
};