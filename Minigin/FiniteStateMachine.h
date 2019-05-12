#pragma once
#include "BaseComponent.h"
#include <unordered_map>
namespace dae
{
	class IState;
	//finite state machine component
	class FiniteStateMachine final
	{
	public:
		FiniteStateMachine(IState* startingState);
		~FiniteStateMachine();
		void Initialize(GameObject* gameObject);
		void Update(float deltaTime, GameObject* gameObject);
		void Render() const {};
		void AddEvent(const std::string& eventName);
		bool IsEventTriggered(const std::string& eventName) const;
		void TriggerEvent(const std::string& eventName);

	private:
		IState* m_pState;
		std::unordered_map<std::string, bool> m_Events;
	};
}


