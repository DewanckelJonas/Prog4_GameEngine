#pragma once
#include "BaseComponent.h"
#include "BaseCommand.h"
#include "InputManager.h"

namespace dae
{
	class PlayerController 
	{
	public:
		PlayerController(GameObject* pActor) :m_pPossesedActor(pActor){};
		~PlayerController();

		void Posses(GameObject* pActor);
		void AddCommand( dae::ControllerButton button, BaseCommand* command);
	private:
		std::vector<BaseCommand*> m_pCommands;
		GameObject* m_pPossesedActor;
	};
}

