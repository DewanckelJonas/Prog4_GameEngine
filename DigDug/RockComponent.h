#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "IState.h"
#include "DigDugLevelComponent.h"
#include "DigDugPlayerComponent.h"
#include "DigDugEnemyComponent.h"
namespace dae { class ColliderComponent; class TransformComponent; }

class RockStable final : public dae::IState
{
public:
	RockStable() = default;
	~RockStable() = default;
	void Enter(const std::weak_ptr<dae::GameObject>& wpGameobject);
	void Exit(const std::weak_ptr<dae::GameObject>&) {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime);

private:
	glm::vec3 m_StartPos;
	float m_TimeTillDrop = 2.f;
	int m_RumbleAmount = 2;
	std::weak_ptr<dae::TransformComponent> m_wpTransformComponet;
	std::weak_ptr<dae::ColliderComponent> m_wpColliderComponent;
	std::weak_ptr<DigDugLevelComponent> m_wpDigDugLevelComponent;
};


class RockFalling final : public dae::IState
{
public:
	RockFalling() = default;
	~RockFalling() = default;
	void Enter(const std::weak_ptr<dae::GameObject>& wpGameobject);
	void Exit(const std::weak_ptr<dae::GameObject>&) {};
	IState* Update(const std::weak_ptr<dae::GameObject>&, float deltaTime);

private:
	float m_DropSpeed = 50.f;
	std::weak_ptr<dae::TransformComponent> m_wpTransformComponet;
	std::weak_ptr<dae::ColliderComponent> m_wpColliderComponent;
	std::weak_ptr<DigDugLevelComponent> m_wpDigDugLevelComponent;
};
class RockComponent final : public BaseComponent
{
public:
	RockComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel) : m_wpLevel(wpLevel) { m_StateMachine = std::make_unique<dae::FiniteStateMachine>(new RockStable); };
	~RockComponent();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const override {};
	const std::weak_ptr<DigDugLevelComponent>& GetLevel() { return m_wpLevel; };
	int GetNrOfEnemiesKilled() { return m_NrOfEnemiesKilled; }
	void AddEnemyKilled() { ++m_NrOfEnemiesKilled; }
private:
	int m_NrOfEnemiesKilled{};
	std::weak_ptr<DigDugLevelComponent> m_wpLevel;
	std::unique_ptr<dae::FiniteStateMachine> m_StateMachine;
};



