#pragma once
#include <memory>
#include "Transform.h"
class BaseComponent;
class ColliderComponent;

namespace dae
{
	class GameObject final
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void Render() const;
		void AddComponent(BaseComponent* pComponent);

		template<class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* pComponent : m_pComponents)
			{
				if (pComponent && typeid(*pComponent) == ti)
					return static_cast<T*>(pComponent);
			}
			return nullptr;
		}


		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::vector<BaseComponent*> m_pComponents;
	};
}
