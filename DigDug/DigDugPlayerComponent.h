#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "BaseCommand.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae { class TransformComponent; class ColliderComponent; }
class DigDugLevelComponent;
class DigDugPlayerComponent : public BaseComponent
{
public:
	DigDugPlayerComponent(std::weak_ptr<DigDugLevelComponent> pLevel);
	~DigDugPlayerComponent() {};
	glm::vec2 GetDirection() { return m_MoveDirection; }
	void SetDirection(const glm::vec2& direction) { m_MoveDirection = direction; }
	void Pump();
	void Die();
	std::weak_ptr<DigDugLevelComponent> GetLevel() { return m_pLevel; };
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const override {};
	void SetForward(glm::vec2 forward) { m_Forward = forward; }
	glm::vec2 GetForward() { return m_Forward; }

private:
	std::weak_ptr<DigDugLevelComponent> m_pLevel;
	std::weak_ptr<dae::TransformComponent> m_pTransform;
	std::weak_ptr<dae::ColliderComponent> m_pCollider;
	std::shared_ptr<dae::FiniteStateMachine> m_StateMachine{};
	glm::vec2 m_MoveDirection{0,0};
	glm::vec2 m_Forward{ 1.f, 0.f };
};

class DigDugMoveCmd final : public dae::BaseCommand
{
public:
	DigDugMoveCmd(const glm::vec2& direction) : m_Direction(direction) {};
	void Execute() override { GetActor().lock()->GetComponent<DigDugPlayerComponent>().lock()->SetDirection(m_Direction); };
private:
	const glm::vec2 m_Direction;
};

class DigDugPumpCommand final : public dae::BaseCommand
{
public:
	DigDugPumpCommand() {};
	void Execute() override { GetActor().lock()->GetComponent<DigDugPlayerComponent>().lock()->Pump(); }
};
