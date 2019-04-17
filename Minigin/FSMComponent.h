#pragma once
#include "BaseComponent.h"
class IState;
namespace dae
{
	class FSMComponent final : public BaseComponent
	{
	public:
		FSMComponent(IState* startingState) :m_pState(startingState) {};
		void Initialize() override{};
		void Update(float deltaTime) override;
		void Render() {} const override;
	private:
		IState* m_pState;
	};
}


