#pragma once
#include "BaseComponent.h"
namespace dae
{
	class IState;
	class FSMComponent final : public BaseComponent
	{
	public:
		FSMComponent(IState* startingState) :m_pState(startingState) {};
		void Initialize() override{};
		void Update(float deltaTime) override;
		void Render() const override {};
	private:
		IState* m_pState;
	};
}


