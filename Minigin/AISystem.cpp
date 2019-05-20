#include "MiniginPCH.h"
#include "AISystem.h"
#include "AIController.h"


void dae::AISystem::AddAIController(const std::shared_ptr<AIController>& spAIController)
{
	spAIController->Initialize();
	m_spAIControllers.push_back(spAIController);
}

std::vector<std::weak_ptr<dae::BaseCommand>> dae::AISystem::Update(float deltaTime)
{
	std::vector<std::weak_ptr<BaseCommand>> wpCommands;
	for (int i = 0; i < int(m_spAIControllers.size()); i++)
	{
		if(!m_spAIControllers[i]->GetActor().lock())
		{
			m_spAIControllers[i] = m_spAIControllers.back();
			m_spAIControllers.pop_back();
			--i;
			continue;
		}

		auto wpCommand = m_spAIControllers[i]->Update(deltaTime);
		if (wpCommand.lock())
			wpCommands.push_back(wpCommand);
	}
	return wpCommands;
}
