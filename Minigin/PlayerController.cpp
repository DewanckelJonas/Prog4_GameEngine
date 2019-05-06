#include "MiniginPCH.h"
#include "PlayerController.h"


dae::PlayerController::~PlayerController()
{
	InputManager::GetInstance().ClearCommands(0);
	for (BaseCommand* pCommand : m_pCommands)
	{
		delete pCommand;
	}
}

void dae::PlayerController::Posses(GameObject * pActor)
{
	m_pPossesedActor = pActor;
	for (BaseCommand* pCommand : m_pCommands)
	{
		pCommand->SetActor(m_pPossesedActor);
	}
}

void dae::PlayerController::AddCommand(dae::ControllerButton button ,BaseCommand * pCommand)
{
	pCommand->SetActor(m_pPossesedActor);
	m_pCommands.push_back(pCommand);
	InputManager::GetInstance().SetCommand(button, pCommand);
}
