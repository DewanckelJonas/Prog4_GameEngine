#pragma once
namespace dae
{
	class GameObject;
	class IState
	{
	public:
		IState() = default;
		virtual void Enter(GameObject*) = 0;
		virtual void Exit(GameObject*) = 0;
		virtual IState* Update(GameObject*, float deltaTime) = 0;
	};
}

