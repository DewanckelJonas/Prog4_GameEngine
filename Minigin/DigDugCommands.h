#pragma once
#include "ICommand.h"
class TransformComponent;
class MoveLeftCmd : public dae::BaseCommand
{
	MoveLeftCmd() = default;
	void SetActor(dae::GameObject* pActor) override;
	void Execute() override;
private:
	TransformComponent* m_pTransformComponent;
};
