#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "BaseCommand.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class DigDugLevelComponent;
class DigDugPlayerComponent : public BaseComponent
{
public:
	DigDugPlayerComponent(DigDugLevelComponent* pLevel);
	~DigDugPlayerComponent();
	glm::vec2 GetDirection() { return m_Direction; }
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
	void Pump();
	void Die();
	DigDugLevelComponent* GetLevel() { return m_pLevel; };
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const override {};

private:
	DigDugLevelComponent* m_pLevel;
	dae::FiniteStateMachine* m_StateMachine{};
	glm::vec2 m_Direction{0,1};
};

class DigDugMoveCmd final : public dae::BaseCommand
{
public:
	DigDugMoveCmd(const glm::vec2& direction) : m_Direction(direction) {};
	void Execute() override { GetActor()->GetComponent<DigDugPlayerComponent>()->SetDirection(m_Direction); };
private:
	const glm::vec2 m_Direction;
};
