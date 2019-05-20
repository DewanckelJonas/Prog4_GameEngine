#include "MiniginPCH.h"
#include "PlayerController.h"


dae::PlayerController::~PlayerController()
{
	InputManager::GetInstance().ClearCommands(0);
}

void dae::PlayerController::Posses(const std::weak_ptr<GameObject>& pActor)
{
	m_pPossesedActor = pActor;

	for (auto pCommand : m_spCommands)
	{
		pCommand->SetActor(m_pPossesedActor);
	}
}

void dae::PlayerController::AddCommand(dae::ControllerButton button ,const std::shared_ptr<BaseCommand>& spCommand)
{
	spCommand->SetActor(m_pPossesedActor);
	m_spCommands.push_back(spCommand);
	InputManager::GetInstance().SetCommand(button, spCommand);
}

void dae::PlayerController::RemoveCommand(dae::ControllerButton button)
{
	InputManager::GetInstance().ClearButton(button, m_ID);
}
