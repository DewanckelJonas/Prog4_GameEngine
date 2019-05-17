#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "BaseCommand.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae { class TransformComponent; }
class DigDugLevelComponent;
class PookaComponent : public BaseComponent
{
public:
	PookaComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel);

	glm::vec2 GetDirection() { return m_MoveDirection; }
	void SetDirection(const glm::vec2& direction) { m_MoveDirection = direction; }
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
	std::shared_ptr<dae::FiniteStateMachine> m_StateMachine{};
	glm::vec2 m_MoveDirection{ 0,0 };
	glm::vec2 m_Forward{ 1.f, 0.f };
};

class PookaMoveCmd final : public dae::BaseCommand
{
public:
	PookaMoveCmd(const glm::vec2& direction) : m_Direction(direction) {};
	void Execute() override { GetActor()->GetComponent<PookaComponent>().lock()->SetDirection(m_Direction); };
private:
	const glm::vec2 m_Direction;
};

class PookaAttackCommand final : public dae::BaseCommand
{
public:
	PookaAttackCommand() {};
	void Execute() override { GetActor()->GetComponent<PookaComponent>().lock()->Die(); }
};


