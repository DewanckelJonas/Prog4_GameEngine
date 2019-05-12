#include "MiniginPCH.h"
#include "DigDugPlayerStates.h"
#include "DigDugPlayerComponent.h"
#include "TransformComponent.h"

void DigDugMoveState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
	m_pTransformComponent = gameObject->GetComponent<dae::TransformComponent>();
}

void DigDugMoveState::Exit(dae::GameObject *)
{
}

dae::IState * DigDugMoveState::Update(dae::GameObject *, float deltaTime)
{
	if (m_pPlayerComponent->GetDirection() == glm::vec2{0,0})
		return new DigDugIdleState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();

	auto movementVec = m_pPlayerComponent->GetDirection()*m_MovementSpeed*deltaTime;
	m_pTransformComponent->Translate(glm::vec3(movementVec.x, movementVec.y, 0));
	return nullptr;
}

void DigDugIdleState::Enter(dae::GameObject * gameObject)
{
	m_pPlayerComponent = gameObject->GetComponent<DigDugPlayerComponent>();
}

dae::IState * DigDugIdleState::Update(dae::GameObject *, float)
{
	if (m_pPlayerComponent->GetDirection() != glm::vec2{0,0})
		return new DigDugMoveState();
	if (IsEventTriggered("Pump"))
		return new DigDugPumpState();
	if (IsEventTriggered("Die"))
		return new DigDugDyingState();
	return nullptr;
}
