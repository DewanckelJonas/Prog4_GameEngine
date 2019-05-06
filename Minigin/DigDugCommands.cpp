#include "MiniginPCH.h"
#include "DigDugCommands.h"
#include "GameObject.h"
#include "TransformComponent.h"



void MoveLeftCmd::SetActor(dae::GameObject * pActor)
{
	BaseCommand::SetActor(pActor);
	m_pTransformComponent = pActor->GetComponent<TransformComponent>();
}

void MoveLeftCmd::Execute()
{
	auto pos = m_pTransformComponent->GetPosition();
	m_pTransformComponent->SetPosition(glm::vec3{ pos.x - 1, pos.y, pos.z });
}
