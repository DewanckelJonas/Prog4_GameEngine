#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
#include "BaseCommand.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Sprite.h"

namespace dae { class TransformComponent; }
class DigDugLevelComponent;
class DigDugEnemyComponent : public BaseComponent
{
public:
	DigDugEnemyComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel);

	glm::vec2 GetDirection() { return m_MoveDirection; }
	void SetDirection(const glm::vec2& direction) { m_MoveDirection = direction; }
	void Die();
	void ToggleGhost();
	virtual void Attack();
	std::weak_ptr<const DigDugLevelComponent> GetLevel() const { return m_pLevel; };
	std::weak_ptr<DigDugLevelComponent> GetLevel() { return m_pLevel; };
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const override {};
	void SetForward(glm::vec2 forward) { m_Forward = forward; }
	glm::vec2 GetForward() { return m_Forward; }
	bool IsGhost() const { return m_IsGhost; }
	void SetGhost(bool value) { m_IsGhost = value; }
	virtual const dae::Sprite& GetWalkSprite() = 0;
	virtual const dae::Sprite& GetGhostSprite() = 0;
	virtual const dae::Sprite& GetBlowUpSprite() = 0;
	virtual const dae::Sprite& GetChargeSprite() = 0;

protected:
	void TriggerEvent(std::string eventName) { m_StateMachine->TriggerEvent(eventName); }

private:
	bool m_IsGhost = false;
	std::weak_ptr<DigDugLevelComponent> m_pLevel;
	std::weak_ptr<dae::TransformComponent> m_pTransform;
	std::shared_ptr<dae::FiniteStateMachine> m_StateMachine{};
	glm::vec2 m_MoveDirection{ 0,0 };
	glm::vec2 m_Forward{ 1.f, 0.f };
};

class EnemyMoveCmd final : public dae::BaseCommand
{
public:
	EnemyMoveCmd(const glm::vec2& direction) : m_Direction(direction) {};
	void Execute() override { GetActor().lock()->GetComponent<DigDugEnemyComponent>().lock()->SetDirection(m_Direction); };
	glm::vec2 GetDirection() const { return m_Direction; }
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
private:
	glm::vec2 m_Direction;
};

class EnemyGhostCommand final : public dae::BaseCommand
{
public:
	EnemyGhostCommand() {};
	void Execute() override { GetActor().lock()->GetComponent<DigDugEnemyComponent>().lock()->ToggleGhost(); }
};

class EnemyFireCommand final : public dae::BaseCommand
{
public:
	EnemyFireCommand() {};
	void Execute() override { GetActor().lock()->GetComponent<DigDugEnemyComponent>().lock()->Attack(); };
};


