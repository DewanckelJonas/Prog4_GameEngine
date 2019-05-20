#pragma once
#include "IState.h"

namespace dae { class TransformComponent; class SpriteComponent; }
class DigDugPlayerComponent;
class DigDugEnemyComponent;
class PumpComponent;
class FygarFireComponent;
class DigDugIdleState final : public dae::IState
{
public:
	DigDugIdleState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime) override;
private:
	std::weak_ptr<DigDugPlayerComponent> m_pPlayerComponent;
};

class DigDugMoveState final : public dae::IState
{
public:
	DigDugMoveState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override;
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime) override;
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
	void Enter(const std::weak_ptr<dae::GameObject>& ) override;
	void Exit(const std::weak_ptr<dae::GameObject>& ) override {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float ) override;
private:
	bool m_CanCancel = false;
	float m_ElapsedSec = 0.f;
	float m_TimeBetweenPumps = 0.5f;
	float m_CancelTime = 0.5f;
	std::weak_ptr<PumpComponent> m_pPump;
	std::weak_ptr<DigDugPlayerComponent> m_pPlayerComponent;
};

class DigDugDyingState final : public dae::IState
{
public:
	DigDugDyingState() {};
	void Enter(const std::weak_ptr<dae::GameObject>& ) override {};
	void Exit(const std::weak_ptr < dae::GameObject > &) override {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float ) override { return nullptr; };

};

class PookaMoveState final : public dae::IState
{
public:
	PookaMoveState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime) override;
private:
	float m_GhostCoolDown = 0.1f;
	std::weak_ptr<DigDugEnemyComponent> m_pPlayerComponent;
	std::weak_ptr<dae::TransformComponent> m_pTransformComponent;
	glm::vec2 m_PrevDirection{ 0,0 };
	float m_MovementSpeed{ 50 };
	float m_GridSnap{ 2.f };
};

class PookaIdleState final : public dae::IState
{
public:
	PookaIdleState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime) override;
private:
	float m_GhostCoolDown = 0.1f; 
	std::weak_ptr<DigDugEnemyComponent> m_pPlayerComponent;
};

class PookaDyingState final : public dae::IState
{
public:
	PookaDyingState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override;
	IState* Update(const std::weak_ptr<dae::GameObject>&, float) override;
private:
	float m_ElapsedSec = 0;
	float m_DeflateTime = 1.5f;
	int m_Health = 3;
	const int m_MaxHealth = 3;
	std::weak_ptr<dae::SpriteComponent> m_pSpriteComp;
};

class PookaGhostState final : public dae::IState 
{
public:
	PookaGhostState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	IState* Update(const std::weak_ptr<dae::GameObject>&, float) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override;
private:
	float m_GridSnap = 2.f;
	float m_Speed = 20.f;
	float m_MinGhostDuration = 0.5f;
	std::weak_ptr<dae::SpriteComponent> m_pSpriteComp;
	std::weak_ptr<DigDugEnemyComponent> m_wpPookaComponent;
	std::weak_ptr<dae::TransformComponent> m_wpTransformComponent;
};

class EnemyFireState final : public dae::IState
{
public:
	EnemyFireState() {};
	void Enter(const std::weak_ptr<dae::GameObject>&) override;
	IState* Update(const std::weak_ptr<dae::GameObject>&, float) override;
	void Exit(const std::weak_ptr<dae::GameObject>&) override;
private:
	std::weak_ptr<DigDugEnemyComponent> m_wpEnemyComponent;
	std::weak_ptr<FygarFireComponent> m_wpFire;
	std::weak_ptr<dae::SpriteComponent> m_wpSpriteComponent;
	float m_ChargeDuration = 0.3f;
	bool m_IsFiring = false;
};