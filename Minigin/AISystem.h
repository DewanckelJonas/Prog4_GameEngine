#pragma once
#include <memory>
#include "Singleton.h"
namespace dae 
{
	class AIController;
	class BaseCommand;
	class AISystem : public Singleton<AISystem>
	{
	public:
		AISystem() = default;
		~AISystem() = default;
		void AddAIController(const std::shared_ptr<AIController>& spAIController);
		std::vector<std::weak_ptr<BaseCommand>> Update(float deltaTime);
	private:
		std::vector<std::shared_ptr<AIController>> m_spAIControllers{};
	};
}

