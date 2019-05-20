#pragma once
#include "BaseComponent.h"
#include "BaseCommand.h"
#include "InputManager.h"
#include <memory>

namespace dae
{
	class PlayerController 
	{
	public:
		PlayerController(std::weak_ptr<GameObject> pActor, size_t id) :m_pPossesedActor(pActor), m_ID(id){};
		~PlayerController();
		void Posses(const std::weak_ptr<GameObject>& pActor);
		void AddCommand( dae::ControllerButton button, const std::shared_ptr<BaseCommand>& command);
		void RemoveCommand(dae::ControllerButton button);
	private:
		std::vector<std::shared_ptr<BaseCommand>> m_spCommands;
		std::weak_ptr<GameObject> m_pPossesedActor;
		size_t m_ID;
	};
}

