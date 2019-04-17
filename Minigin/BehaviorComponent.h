#pragma once
#include "BaseComponent.h"

#include "IBehavior.h";
namespace dae
{
	class BehaviorComponent final : public BaseComponent
	{
	public:
		BehaviorComponent(IBehavior* pBehavior) :m_pBehavior(pBehavior) {};
		~BehaviorComponent() { delete m_pBehavior; }

		void Initialize() override { m_pBehavior->Initialize(); }
		void Update(float deltaTime) override { m_pBehavior->Update(GetGameObject(), deltaTime); }
		void Render() const override {};

	private:
		IBehavior*  m_pBehavior;
	};
}

