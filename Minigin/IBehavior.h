#pragma once
namespace dae
{
	class GameObject;
	class IBehavior
	{
	public:
		IBehavior() = default;
		virtual void Initialize(GameObject* pObject) = 0;
		virtual void Update(GameObject* pObject, float deltaTime) = 0;
	};
}

