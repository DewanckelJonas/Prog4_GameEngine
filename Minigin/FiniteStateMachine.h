#pragma once
#include "BaseComponent.h"
namespace dae
{
	class IState;
	//finite state machine component
	class FiniteStateMachine final
	{
	public:
		FiniteStateMachine(IState* startingState) :m_pState(startingState) {};
		~FiniteStateMachine();
		void Initialize() {};
		void Update(float deltaTime, GameObject* gameObject);
		void Render() const {};
	private:
		IState* m_pState;
	};
}


