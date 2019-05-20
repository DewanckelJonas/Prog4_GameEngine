#pragma once
#include <memory>
#include "BaseCommand.h"
#include <map>
namespace dae
{
	class GameObject;
	class AIController
	{
	public:
		AIController(const std::weak_ptr<GameObject>& pActor) :m_pPossesedActor(pActor){};
		virtual ~AIController() = default;
		virtual void Initialize() = 0;
		virtual std::weak_ptr<BaseCommand> Update(float deltaTime) = 0;
		std::weak_ptr<const GameObject> GetActor() { return m_pPossesedActor; };

	protected:
		void SetActor(const std::weak_ptr<BaseCommand>& wpCommand) { wpCommand.lock()->SetActor(m_pPossesedActor); };
	private:
		std::weak_ptr<GameObject> m_pPossesedActor;
	};
}

