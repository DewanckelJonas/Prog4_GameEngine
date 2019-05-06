#pragma once
#include "BaseComponent.h"
namespace dae
{
	class IState;
	//finite state machine component
	class FSMComponent final : public BaseComponent
	{
	public:
		FSMComponent(IState* startingState) :m_pState(startingState) {};
		~FSMComponent();
		void Initialize() override{};
		void Update(float deltaTime) override;
		void Render() const override {};
	private:
		IState* m_pState;
	};
}


