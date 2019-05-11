#pragma once
#include "BaseComponent.h"
#include "FiniteStateMachine.h"
class DigDugPlayerComponent : public BaseComponent
{
public:
	DigDugPlayerComponent();
	~DigDugPlayerComponent();
private:
	
	dae::FiniteStateMachine m_StateMachine;
};

